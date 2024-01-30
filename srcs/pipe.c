/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:17:15 by npirard           #+#    #+#             */
/*   Updated: 2024/01/30 10:23:16 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <errno.h>
#include <fcntl.h>

static int	handle_command(t_command *command, int *fd,
				int *old_fd, t_data *data);
int			exec_pipe(t_list *commands, t_data *data, int *old_fd);

/// @brief A command is defined as such [(< file_in)*n][ cmd][(> file_out)*n]
/// @param command
/// @param fd File descriptors of output pipe. ```NULL``` if last command.
/// @param old_fd File descriptors of input pipe. ```NULL``` if first command.
/// @param env
/// @return Process id of command if executed.
///```-1``` if error. Can occurs during in or out redirection, during piping,
/// during forking or during argv metachar interpretation and conversion
/// ```0``` if builtin succeed n in parent or no command was given
/// (only redirection).
/// ```< 0``` corresponding to builtin exit status if failed in parent.
static int	handle_command(t_command *command, int *old_fd,
				int *fd, t_data *data)
{
	int		id;
	char	**argv;
	int		err;

	id = 0;
	if (handle_redirection(command->files, old_fd, fd, data))
		return (-1);
	err = interpret_argv(&command->argv, data);
	argv = ft_lsttostrs(command->argv);
	if (err)
	{
		if (old_fd)
			close(STDIN_FILENO);
		ft_free_strs(argv);
		return (-1);
	}
	if (argv)
		id = exec_command(argv, fd, old_fd, data);
	if (id < 0 && old_fd)
		close(STDIN_FILENO);
	ft_free_strs(argv);
	return (id);
}

/// @brief A pipe is defined as a list of ```t_command``` separated by ```|```.
/// This function recursively execute every command in the list iterating
/// through ```commands``` pointer.
/// @param commands List of ```t_command``` structures.
/// @param env
/// @param old_fd Previous command's pipe fd. ```NULL``` for first command.
/// @return Last command's process id. ```<= 0``` if last command was
/// a builtin executed in parent (in this case it represents the exit status)
/// or last command failed before execution.
int	exec_pipe(t_list *commands, t_data *data, int *old_fd)
{
	int		fd[2];
	int		id;

	errno = 0;
	if (commands->next)
	{
		handle_command((t_command *) commands->content, old_fd, fd, data);
		if (restore_std(data))
			return (-1);
		id = exec_pipe(commands->next, data, fd);
	}
	else
		id = handle_command((t_command *) commands->content,
				old_fd, NULL, data);
	if (restore_std(data))
		return (-1);
	return (id);
}
