/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:37:35 by npirard           #+#    #+#             */
/*   Updated: 2024/01/15 10:28:07 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <string.h>
#include <errno.h>
#include <minishell.h>

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
/// @param err 1 = parse error near || 2 = ambiguous redirect
/// @param str
/// @return ```err```
int	parse_error(int err, char *str)
{
	errno = err;
	if (err == 1)
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	else if (err == 2)
		ft_putstr_fd("minishell: ambiguous redirect: ", 2);
	if (err == -1)
	{
		ft_putstr_fd("minishell: Allocation error", 2);
		exit(-1);
	}
	if (str && err == 1)
	{
		write(2, "`", 1);
		write(2, str, ft_strlen(str));
		write(2, "\'\n", 2);
	}
	else if (str && err == 2)
		ft_putendl_fd(str, 2);
	return (err);
}

/// @brief Set errno to err, and print error with given builtin name
/// and given value & context if provided
/// @param err
/// @param builtin Name of the builtin command
/// @param value Can be left to ```NULL```
/// @param context Can be left to ```NULL```
/// @return ```err```
/// @note format : "minishell: $builtin[: value][: context]"
int	builtin_error(int err, char *builtin, char *value, char *context)
{
	errno = err;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(builtin, 2);
	if (value)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(value, 2);
	}
	if (context)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(context, 2);
	}
	ft_putstr_fd("\n", 2);
	return (err);
}


