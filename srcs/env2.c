/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:06:33 by npirard           #+#    #+#             */
/*   Updated: 2024/01/09 11:28:05 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <errno.h>

/// @brief Return ```true``` is given var is defined in env.
/// A defined variable can be empty.
/// @param var
/// @param env
/// @return
bool	is_var_defined(char *var, char **env)
{
	while (*env && ft_strncmp(*env, var, ft_strlen(var)))
		env++;
	if (*env)
		return (true);
	return (false);
}
