/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:17:15 by npirard           #+#    #+#             */
/*   Updated: 2024/01/16 09:22:07 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <errno.h>
#include <fcntl.h>

static int	redirection_in(t_file_rd *file);
static int	redirection_out(t_file_rd *file);
static int	handle_redirection(t_list *files, int *old_fd, int *fd,
				t_data *data);
static int	handle_command(t_command *command, int *fd,
				int *old_fd, t_data *data);
int			exec_pipe(t_list *commands, t_data *data, int *old_fd);

/// @brief
/// @param file t_file_rd struct
/// @param old_fd File descripors of input pipe. ```NULL``` for first command.
/// @return ```0``` if no error. Else ```errno```.
static int	redirection_in(t_file_rd *file)
{
	if (file_redirect(file->path, STDIN_FILENO, O_RDONLY))
		return (errno);
	if (file->type == 1 && unlink(file->path) < 0)
		return (error(errno, file->path));
	return (0);
}

/// @brief
/// @param file t_file_rd struct
/// @param fd File descripors of output pipe. ```NULL``` for last command.
/// @return ```0``` if no error. Else ```errno```.
static int	redirection_out(t_file_rd *file)
{
	int			o_flag;

	o_flag = O_RDWR | O_TRUNC | O_CREAT;
	if (file->type == 3)
		o_flag = O_APPEND | O_RDWR | O_CREAT;
	if (file_redirect(file->path, STDOUT_FILENO, o_flag))
		return (errno);
	return (0);
}

/// @brief Handle file and pipe redirection
/// @param files List of file redirection
/// @param old_fd File descripors of input pipe. ```NULL``` for first command.
/// @param fd File descripors of output pipe. ```NULL``` for last command.
/// @param data
/// @return ```0``` for success. ```errno``` if error.
static int	handle_redirection(t_list *files, int *old_fd,
				int *fd, t_data *data)
{
	t_file_rd	*file;

	if (old_fd && dup_and_close(old_fd[0], STDIN_FILENO))
		return (error(errno, NULL));
	while (files)
	{
		file = (t_file_rd *) files->content;
		if (check_file_meta(file, data))
			return (errno);
		if (file->type <= 1)
		{
			if (old_fd)
				clear_pipe(0, old_fd[0]);
			old_fd = NULL;
			if (redirection_in(file))
				return (errno);
		}
		else if (file->type >= 2 && redirection_out(file))
			return (errno);
		files = files->next;
	}
	if (fd && (pipe(fd) < 0 || dup_and_close(fd[1], STDOUT_FILENO)))
		return (error(errno, NULL));
	return (0);
}

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
	err = interpret_argv(command->argv, data);
	argv = ft_lsttostrs(command->argv);
	if (!argv || err)
	{
		if (old_fd)
			clear_pipe(0, 0);
		return (-1);
	}
	if (command->argv)
		id = exec_command(argv, fd, old_fd, data);
	if (id < 0 && old_fd)
		clear_pipe(0, 0);
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
