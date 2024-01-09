/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:49:58 by npirard           #+#    #+#             */
/*   Updated: 2024/01/09 15:41:29 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

/// @brief Return the path of a dir if it can be found in one of
/// ```path_strs```'s path and if the file is a directory. Free dir
/// if path is found or alloc error.
/// @param dir
/// @param path_strs
/// @return Path of given dir, dir if path not found
/// NULL if alloc error
static char	*build_path(char *dir, char **path_strs)
{
	char	*path;

	while (*path_strs)
	{
		path = path_join(*path_strs++, dir);
		if (!path)
		{
			free(dir);
			return (NULL);
		}
		if (access(path, F_OK) == 0 && is_directory(path))
		{
			free(dir);
			return (path);
		}
		free(path);
	}
	return (dir);
}

/// @brief Look for match of path in CDPATH variable.
/// @param path must be a relative path
/// @param env CDPATH must be declared
/// @return absolute path of the match if found.
/// If no match, path is returned.
/// ```NULL``` if allocation error.
static char	*find_cdpath(char *path, char **env)
{
	char	*cdpath_value;
	char	**cdpath_strs;

	cdpath_value = get_var_value("CDPATH", env);
	if (!cdpath_value)
	{
		free(path);
		return (NULL);
	}
	cdpath_strs = ft_split(cdpath_value, ':');
	if (!cdpath_strs)
	{
		free(cdpath_value);
		free(path);
		return (NULL);
	}
	path = build_path(path, cdpath_strs);
	free(cdpath_value);
	ft_free_strs(cdpath_strs);
	return (path);
}

/// @brief Look for a dest path and assign it to the string pointed
/// by buf.
/// @param buf Pointer toward buffer receiving the final path to use.
/// It needs to be freed externally.
/// @param path Can be a relative or an absolute path. Can be ```NULL```
/// (in this case HOME variable will be used if defined)
/// @param env HOME can be used if no argument is given (path is NULL).
/// If path is relative and does not refer to an existing directory in the
/// the working directory, it is then searched in CDPATH (if defined).
/// @return ```0``` for success (meaning the final path is an existing
/// existing directory), or final path is empty (either given as such or
/// found in HOME).
/// ```1``` if error (undefined HOME or no directory found).
/// ```2``` allocation error.
int	cd_find_path(char **buf, char *path, char **env)
{
	if (!path && !is_var_defined("HOME", env))
		return (builtin_error(1, "cd", NULL, "HOME not set"));
	else if (!path)
		*buf = get_var_value("HOME", env);
	else
		*buf = ft_strdup(path);
	if (!*buf)
		return (builtin_error(errno, "cd", NULL, "Allocation error"));
	if (!*buf[0] || (!access(*buf, F_OK) && is_directory(*buf)))
		return (0);
	else if (!is_abs_path(*buf) && is_var_defined("CDPATH", env) && path)
	{
		*buf = find_cdpath(*buf, env);
		if (!*buf)
			return (builtin_error(errno, "cd", "CDPATH", "Allocation error"));
	}
	if (!access(*buf, F_OK) && !is_directory(*buf))
		return (builtin_error(1, "cd", path, "Not a directory"));
	else if (access(*buf, F_OK))
		return (builtin_error(1, "cd", *buf, strerror(errno)));
	return (0);
}
