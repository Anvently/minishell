/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:09:32 by npirard           #+#    #+#             */
/*   Updated: 2024/01/30 10:30:26 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

/// @brief Return the path of a command if it can be found in one of
/// ```path_strs```'s path and if the file is executable.
/// @param command
/// @param path_strs
/// @return Path of given command, ```NULL``` if allocation error
/// or path not found.
static char	*build_path(char *command, char **path_strs)
{
	char	*path;

	path = NULL;
	while (*path_strs)
	{
		path = path_join(*path_strs++, command);
		if (!path)
		{
			error(errno, "joining cmd path");
			return (NULL);
		}
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		path = NULL;
	}
	return (path);
}

/// @brief Search for ```PATH``` variable in ```env``` and split it into
/// a list of strings.
/// @param env
/// @return List of strings for each path inside ```PATH``` variable.
/// ```NULL``` if allocation error or if no ```PATH``` variable is found in env.
static char	**split_path(char **env)
{
	char	*var_path;
	char	**path_strs;

	path_strs = NULL;
	var_path = get_var_value("PATH", env);
	if (var_path)
	{
		path_strs = ft_split(var_path, ':');
		free(var_path);
		if (!path_strs)
			return (alloc_error());
	}
	return (path_strs);
}

/// @brief Check if given command is a path or can be found in PATH variable.
/// Free command and return the full path if found.
/// @param command
/// @param env
/// @return ```0``` for success (if found, absolute path or builtin).
/// ```1``` if command not found or allocation error
int	command_find_path(char *command, char **path_dest, char **env)
{
	char		**path_strs;
	char		*path;

	if (is_abs_path(command) || command_is_builtin(command) || !env)
		return (0);
	if (!command[0])
	{
		builtin_error(errno, "''", NULL, "command not found");
		return (errno);
	}
	path_strs = split_path(env);
	if (!path_strs)
		return (0);
	path = build_path(command, path_strs);
	ft_free_strs(path_strs);
	if (!path && errno != ENOMEM)
		builtin_error(errno, command, NULL, "command not found");
	if (path)
	{
		free(command);
		*path_dest = path;
		return (0);
	}
	return (127);
}
