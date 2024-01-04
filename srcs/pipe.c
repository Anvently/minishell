/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:17:15 by npirard           #+#    #+#             */
/*   Updated: 2024/01/04 11:26:55 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <errno.h>

static int	handle_files_in(t_list *files_in, int *old_fd);
static int	handle_file_out(t_list *files_out, int *fd);
static int	handle_command(t_command *command, int *fd,
				int *old_fd, char **env);
int			exec_pipe(t_list *commands, char **env, int *old_fd);

/// @brief 1. Check infiles
/// 		- if infile
/// 			- open and dup
/// 			- if old_fd
/// 				- clear old_fd[0]
/// 		- if no infile
/// 			- if old_fd
/// 				- stdin = old_fd[0]
/// 				- close(old_fd[0])
/// 			-else
/// 				- do nothing
/// @param files_in List of string for files' path.
/// @param old_fd File descripors of input pipe. ```NULL``` for first command.
/// @return ```0``` if no error. Else ```errno```.
static int	handle_files_in(t_list *files_in, int *old_fd)
{
	if (files_in)
	{
		// Clear old_fd if not NULL (avoid memory leak)
		// Open each file and dup stdin
			// Stop at fist fail.
		// return (0);
	}
	if (old_fd)
	{
		// Dup stdin from input pipe.
	}
	return (0);
}

/// @brief 2. Check outfile
/// 		- if not last
/// 			- pipe
/// 		- if outfile
/// 			- open and dup
/// 		- if no outfile
/// 			- if not last
/// 				- stdout = fd[1]
/// 				- close(fd[1])
/// 			- else
/// 				- do nothing to stdout
/// @param files_out
/// @param fd
/// @return
static int	handle_file_out(t_list *files_out, int *fd)
{

}

/// @brief A command is defined as such [(< file_in)*n][ cmd][(> file_out)*n]
/// @param command
/// @param fd File descriptors of output pipe. ```NULL``` if last command.
/// @param old_fd File descriptors of input pipe. ```NULL``` if first command.
/// @param env
/// @return Process id of command if executed. ```-1``` if error. ```0``` if builtin
/// succeed n in parent. ```negative number``` corresponding to builtin exit status if
/// failed in parent.
static int	handle_command(t_command *command, int *fd,
				int *old_fd, char **env)
{
	int	status;
	int	id;

	if (handle_files_in(command->files_in, old_fd)
		&& handle_file_out(command->files_out, fd))
	{
		// Search command
			// If not absolute path && not builtin
				// Search in path
		// if found || bultin
			// If not (!fd && !old_fd && builtin)
				// fork
			// Else
				// id = -2
			// If bultin
				/// Clear old_fd
				// Exec bultin
				// If id == 0;
					// Exit (builtin_status)
				// id = - builtin_status
			// Else
				// Execve
			// Clear old_fd
		return (id);
	}
	return (-1);
}

/// @brief A pipe is defined as a list of ```t_command``` separated by ```|```.
/// This function recursively execute every command in the list iterating
/// through ```commands``` pointer.
/// @param commands List of ```t_command``` structures.
/// @param env
/// @param old_fd Previous command's pipe fd. ```NULL``` for first command.
/// @return Last command's process id. ```<= 0``` if last command was
/// a builtin executed in parent (in this case it represents the exit status)
int	exec_pipe(t_list *commands, char **env, int *old_fd)
{
	int		fd[2];
	int		id;

	if (commands->next)
	{
		if (pipe(fd))
			return (error(errno, NULL));
		handle_command((t_command *) commands->content, fd, old_fd, env);
		id = exec_pipe(commands->next, env, fd);
	}
	else
		id = handle_command((t_command *) commands->content,
				NULL, old_fd, env);
	return (id);
}
