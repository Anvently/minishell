/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:10:44 by npirard           #+#    #+#             */
/*   Updated: 2024/01/17 15:55:47 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <errno.h>
#include <string.h>

/// @brief Print str to stdout.
/// @param str
/// @return ```0``` if no error or ```errno``` if write error.
static int	put_str(char *str)
{
	if (write(1, str, ft_strlen(str)) < 0)
		return (builtin_error(errno, "echo", NULL, strerror(errno)));
	return (0);
}

/// @brief Print given arguments (separated with spaces) to stdout and followed
/// by a newline (unless -n flag is given).
/// @param argv Can be ```NULL``` or empty.
/// @return ```0``` or ```errno``` if a write error occurs.
int	builtin_echo(char **argv)
{
	bool	newline;

	newline = true;
	if (!argv || ft_strslen(argv) < 2)
		return (put_str("\n"));
	while (argv[1] && (!ft_strncmp("-n", argv[1], 2) || !argv[1][0]))
	{
		if (!ft_strncmp("-n", argv[1], 2))
			newline = false;
		argv ++;
	}
	while (argv[1])
	{
		if (put_str(argv[1]))
			return (errno);
		if (argv[2] && argv[1][0] && argv[2][0])
			if (put_str(" "))
				return (errno);
		argv++;
	}
	if (newline)
		if (put_str("\n"))
			return (errno);
	return (0);
}
