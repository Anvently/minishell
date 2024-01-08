/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:48:41 by npirard           #+#    #+#             */
/*   Updated: 2024/01/08 16:45:10 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <unistd.h>
#include <errno.h>

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
int	exec_builtin(t_command *command, t_data *data)
{
	if (!ft_strcmp(command->argv[0], "export"))
		return (builtin_export(command->argv, data->env));
	else if (!ft_strcmp(command->argv[0], "env"))
		return (builtin_env(*data->env));
	else if (!ft_strcmp(command->argv[0], "echo"))
		return (builtin_echo(command->argv));
	else if (!ft_strcmp(command->argv[0], "exit"))
	{
		//Free data
		ft_free_strs(*data->env);
		builtin_exit(command->argv);
	}
	else if (!ft_strcmp(command->argv[0], "unset"))
		return (builtin_unset(command->argv, *data->env));
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
int	exec_command(t_command *command, int *fd, int *old_fd, t_data *data)
{
	int	id;

	command->argv[0] = command_find_path(command->argv[0], *data->env);
	id = command_check_fork(!(!fd && !old_fd
				&& command_is_builtin(command->argv[0])), command->argv[0]);
	if (id == -1)
		return (id);
	if (command_is_builtin(command->argv[0]))
		clear_pipe(old_fd[0]);
	if (id == 0)
	{
		if (command_is_builtin(command->argv[0]))
			exit(free_data(exec_builtin(command, data), data));
		if (execve(command->argv[0], command->argv, *data->env))
		{
			clear_pipe(old_fd[0]);
			exit(error(errno, command->argv[0]));
		}
	}
	else if (id == -2)
		id = -exec_builtin(command, data);
	return (id);
}
