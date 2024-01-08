/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:15:41 by npirard           #+#    #+#             */
/*   Updated: 2024/01/08 17:19:57 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <linux/limits.h>
#include <minishell.h>
#include <string.h>

/// @brief Print str to STDOUT_FILENO.
/// @param str
/// @return ```0``` if no error or ```errno``` if write error.
static int	put_str(char *str)
{

	if (write(1, str, ft_strlen(str)) < 0)
		return (builtin_error(errno, "echo", str));
	return (0);
}

/// @brief Print to stdout name of current working directory.
/// @param argv
/// @return ```0``` for success.
/// ```1``` for write error.
int	builtin_pwd(void)
{
	char	path[PATH_MAX];

	if (!getcwd(path, PATH_MAX))
		return (builtin_error(errno, "pwd", strerror(errno)));
	if (put_str(path))
		return (builtin_error(errno, "pwd", path));
	if (put_str("\n"))
		return (builtin_error(errno, "pwd", path));
	return (0);
}
