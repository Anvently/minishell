/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:37:52 by npirard           #+#    #+#             */
/*   Updated: 2024/01/05 15:03:12 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <errno.h>

/// @brief Print str to stdout.
/// @param str
/// @return ```0``` if no error or ```errno``` if write error.
static int	put_str(char *str)
{

	if (write(1, str, ft_strlen(str)) < 0)
		return (builtin_error(errno, "env", str));
	return (0);
}

/// @brief Print env
/// @param env
/// @return ```0``` if success, ```errno``` if write error.
int	builtin_env(char **env)
{
	while (env && *env)
	{
		if (put_str(*env))
			return (errno);
		if (*(env + 1) && put_str("\n"))
			return (errno);
		env++;
	}
	if (put_str("\n"))
		return (errno);
	return (0);
}
