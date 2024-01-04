/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:09:32 by npirard           #+#    #+#             */
/*   Updated: 2024/01/04 16:30:02 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

/// @brief Allocate and return the concatenation of path and command, adding a
/// '/' in between.
/// @param path Null terminated string
/// @param command Null terminated string
/// @return Address of allocated string
/// NULL if allocation fails.
static char	*path_join(char const *path, char const *command)
{
	char	*buffer;
	size_t	size;
	size_t	len_path;
	size_t	len_command;

	len_path = ft_strlen(path);
	len_command = ft_strlen(command);
	if (!path || !command)
		return (NULL);
	size = len_path + len_command + 2;
	buffer = malloc(size);
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, path, size);
	buffer[len_path] = '/';
	buffer[len_path + 1] = '\0';
	ft_strlcat(buffer, command, size);
	return (buffer);
}

/// @brief Return the path of a command if it can be found in one of
/// ```path_strs```'s path and if the file is executable. Free command
/// if path is found or alloc error.
/// @param command
/// @param path_strs
/// @return Path of given command, command if path not found
/// NULL if alloc error
static char	*build_path(char *command, char **path_strs)
{
	char	*path;

	while (*path_strs)
	{
		path = path_join(*path_strs++, command);
		if (!path)
		{
			free(command);
			return (alloc_error());
		}
		if (access(path, X_OK) == 0)
		{
			free(command);
			return (path);
		}
	}
	return (command);
}

/// @brief Search for ```PATH``` variable in ```env``` and split it into
/// a list of strings.
/// @param env
/// @return List of strings for each path inside ```PATH``` variable.
/// ```NULL``` if allocation error or if no ```PATH``` variable is found in env.
static char	**split_path(char **env)
{
	char	*sub_path;
	char	**path_strs;

	path_strs = NULL;
	while (*env && ft_strncmp(*env, "PATH=", 5))
		env++;
	if (*env)
	{
		sub_path = ft_substr(*env, 5, ft_strlen(*env) - 5);
		if (!sub_path)
			return (alloc_error());
		path_strs = ft_split(sub_path, ':');
		free(sub_path);
		if (!path_strs)
			return (alloc_error());
	}
	return (path_strs);
}

/// @brief Check if given command is a path or can be found in PATH variable.
/// Free command and return the full path if found.
/// @param command
/// @param env
/// @return Path of the command to execute if correct. Command as such if
/// PATH is unset or if command is a builtin.
char	*command_find_path(char *command, char **env)
{
	char		**path_strs;

	if (command_is_path(command) || command_is_builtin(command) || !env)
		return (command);
	path_strs = split_path(env);
	if (!path_strs)
		return (command);
	command = build_path(command, path_strs);
	ft_free_strs(path_strs);
	return (command);
}
