/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:21:20 by npirard           #+#    #+#             */
/*   Updated: 2024/01/16 09:37:34 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>

/// @brief Check if given command is one of these builtin :
/// echo, cd, pwd, export, unset, env, exit
/// @param command
/// @return
bool	command_is_builtin(char *command)
{
	if (!command)
		return (false);
	if (ft_strschr((char *[]){"echo", "cd", "pwd", "export",
			"unset", "env", "exit", NULL}, command))
		return (true);
	return (false);
}
