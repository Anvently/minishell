/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:21:20 by npirard           #+#    #+#             */
/*   Updated: 2024/01/04 14:39:53 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>

/// @brief Check if the command is already a path. Meaning it starts with a
/// ```.```, a ```~``` or a ```/```
/// @param command
/// @return ```true``` if command is a path, else ```false```.
bool	command_is_path(char *command)
{
	if (ft_strchr("./~", command[0]))
		return (true);
	return (false);
}

bool	path_exist(char *path, bool printerr)
{
	if (access(path, F_OK) == 0)
		return (true);
	if (printerr)
		error_path("No such file or directory", path);
	return (false);
}

bool	path_is_exec(char *path, bool printerr)
{
	if (access(path, X_OK) == 0)
		return (true);
	if (printerr)
		error_path("Permission denied", path);
	return (false);
}

/// @brief Check if given command is one of these builtin :
/// echo, cd, pwd, export, unset, env, exit
/// @param command
/// @return
bool	is_builtin(char *command)
{
	if (ft_strschr((char *[]){"echo", "cd", "pwd", "export",
			"unset", "env", "exit", NULL}, command))
		return (true);
	return (false);
}
