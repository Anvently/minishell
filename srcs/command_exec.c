/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:48:41 by npirard           #+#    #+#             */
/*   Updated: 2024/01/12 18:06:40 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <unistd.h>
#include <errno.h>

static int	command_check_fork(bool child, char *command);
int			exec_builtin(char **argv, t_data *data);
int			exec_command(char **argv, int *fd, int *old_fd, t_data *data);

/// @brief Fork if child is ```false```.
/// @param child Determines if command is a builtin that needs to be
/// executed in parent or in a child process
/// @param command path to the command. Used only for error printing.
/// Can be set to ```NULL```.
/// @return ```> 0``` for child's process if fork occured.
/// ```0``` for child process.
/// ```-2``` if we are still in parent and no fork occured.
/// ```-1``` if an error occured while forking. The error is printed.
static int	command_check_fork(bool child, char *command)
{
	int	id;

	if (child)
	{
		id = fork();
		if (id < 0)
		{
			error(errno, command);
			return (-1);
		}
	}
	else
		id = -2;
	return (id);
}

/// @brief Exec a builtin command
/// @param command
/// @param env
/// @return builtin exit status.
/// ```0``` if command is not a builtin.
int	exec_builtin(char **argv, t_data *data)
{
	if (!ft_strcmp(argv[0], "export"))
		return (builtin_export(argv, &data->env));
	else if (!ft_strcmp(argv[0], "env"))
		return (builtin_env(data->env));
	else if (!ft_strcmp(argv[0], "echo"))
		return (builtin_echo(argv));
	else if (!ft_strcmp(argv[0], "exit"))
	{
		free_data(0, data);
		builtin_exit(argv);
	}
	else if (!ft_strcmp(argv[0], "unset"))
		return (builtin_unset(argv, &data->env));
	return (0);
}

/// @brief Execute the given command. Command is searched in PATH variabe if
/// if necessary.
/// Command is always executed in a child process EXCEPT if there is NO PIPE
/// and command is a BUILTIN.
/// @param command
/// @param fd File descriptors of output pipe. ```NULL``` if last command.
/// @param old_fd File descriptors of input pipe. ```NULL``` if first command.
/// @return Process id of command if executed.
///```-1``` if error while forking.
/// ```0``` if builtin succeed n in parent
/// ```< 0``` corresponding to builtin exit status if failed in parent.
int	exec_command(char **argv, int *fd, int *old_fd, t_data *data)
{
	int	id;

	argv[0] = command_find_path(argv[0], data->env);
	id = command_check_fork(!(!fd && !old_fd
				&& command_is_builtin(argv[0])), argv[0]);
	if (id == -1)
		return (id);
	if (command_is_builtin(argv[0]) && old_fd)
		clear_pipe(0, 0);
	if (id == 0)
	{
		if (command_is_builtin(argv[0]))
			exit(free_data(exec_builtin(argv, data), data));
		if (execve(argv[0], argv, data->env))
		{
			error(errno, argv[0]);
			return (-1);
		}
	}
	else if (id == -2)
		id = -exec_builtin(argv, data);
	return (id);
}
