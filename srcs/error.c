/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:37:35 by npirard           #+#    #+#             */
/*   Updated: 2024/01/04 16:09:10 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <string.h>
#include <errno.h>

int	error(int err, char *str)
{
	ft_putstr_fd(strerror(err), 2);
	if (str)
	{
		write(2, ": ", 2);
		ft_putstr_fd(str, 2);
	}
	write(2, "\n", 1);
	return (err);
}

/// @brief
/// @param err
/// @param str
/// @return
int parse_error(int err, char *str)
{
	if (error == 1)
		ft_putstr_fd("minishell: XXXXX: ", 2);
	else if (error == 2)
		ft_putstr_fd("minishell: ambiguous redirect: ", 2);
	if (str)
		ft_putendl_fd(str, 2);
	return (err);
}
