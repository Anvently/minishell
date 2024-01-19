/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:53:50 by npirard           #+#    #+#             */
/*   Updated: 2024/01/19 10:52:18 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <libft.h>
#include <minishell.h>
#include <errno.h>

bool	is_abs_path(char *str);
bool	is_directory(char *path);
char	*path_join(char const *path, char const *tail);

/// @brief Check if the string is a path. Meaning it starts with one
/// or more```.```  followed with a ```/``` or start with a ```/```.
/// @param str
/// @return ```true``` if str is a path, else ```false```.
bool	is_abs_path(char *str)
{
	while (*str == '.')
		str++;
	if (*str == '/')
		return (true);
	return (false);
}

/// @brief Check if given path is a directory
/// @param path
/// @return
bool	is_directory(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

/// @brief Allocate and return the concatenation of path and tail, adding a
/// '/' in between.
/// @param path Null terminated string
/// @param tail Null terminated string
/// @return Address of allocated string
/// NULL if allocation fails.
char	*path_join(char const *path, char const *tail)
{
	char	*buffer;
	size_t	size;
	size_t	len_path;
	size_t	len_tail;

	len_path = ft_strlen(path);
	len_tail = ft_strlen(tail);
	if (!path || !tail)
		return (NULL);
	size = len_path + len_tail + 2;
	buffer = malloc(size);
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, path, size);
	buffer[len_path] = '/';
	buffer[len_path + 1] = '\0';
	ft_strlcat(buffer, tail, size);
	return (buffer);
}
