/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:37:35 by npirard           #+#    #+#             */
/*   Updated: 2024/01/08 17:03:12 by npirard          ###   ########.fr       */
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
		ft_putstr_fd("minishell: XXXXX: ", 2);
	else if (err == 2)
		ft_putstr_fd("minishell: ambiguous redirect: ", 2);
	if (str)
		ft_putendl_fd(str, 2);
	return (err);
}

/// @brief Set errno to err, and print error with given builtin name
/// and given context if provided
/// @param err
/// @param builtin Name of the builtin command
/// @param context Can be left to ```NULL```
/// @return ```err```
int	builtin_error(int err, char *builtin, char *context)
{
	errno = err;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(builtin, 2);
	ft_putstr_fd(": ", 2);
	if (context)
		ft_putendl_fd(context, 2);
	return (err);
}

/// @brief Free all data and return given err code.
/// @param err
/// @param data
/// @return ```err```
int	free_data(int err, t_data *data)
{
	//free pipe_list
	ft_free_strs(*data->env);
	*data->env = NULL;
	return (err);
}
