/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:21:20 by npirard           #+#    #+#             */
/*   Updated: 2024/01/04 15:50:30 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>

/// @brief Check if the command is already a path. Meaning it starts with one
/// or more```.```  followed with a ```/``` or start with a ```/```.
/// @param command
/// @return ```true``` if command is a path, else ```false```.
bool	command_is_path(char *command)
{
	while (*command == '.')
		command++;
	if (*command == '/')
		return (true);
	return (false);
}

bool	path_exist(char *path)
{
	if (access(path, F_OK) == 0)
		return (true);
	return (false);
}

bool	path_is_exec(char *path)
{
	if (access(path, X_OK) == 0)
		return (true);
	return (false);
}

/// @brief Check if given command is one of these builtin :
/// echo, cd, pwd, export, unset, env, exit
/// @param command
/// @return
bool	command_is_builtin(char *command)
{
	if (ft_strschr((char *[]){"echo", "cd", "pwd", "export",
			"unset", "env", "exit", NULL}, command))
		return (true);
	return (false);
}
