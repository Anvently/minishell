/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_argv2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:27:57 by npirard           #+#    #+#             */
/*   Updated: 2024/01/18 14:33:46 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

/// @brief Check if a string is contained within parenthesis.
/// Ignore any space before string. Only opening parenthesis is checked,
/// correct enclosure is not checked here.
/// @param str
/// @return ```true``` if inside parenthesis else ```false```.
bool	is_inside_parenthesis(char *str)
{
	while (ft_isspace(*str))
		str++;
	if (*str == '(')
		return (true);
	return (false);
}
