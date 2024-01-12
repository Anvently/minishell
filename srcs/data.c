/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:31:05 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/12 14:50:29 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parse.h>
#include <libft.h>

/// @brief Free all data and return given err code.
/// @param err
/// @param data
/// @return ```err```
int	free_data(int err, t_data *data)
{
	ft_lstclear(&data->pipe_list, free_t_pipe);
	ft_free_strs(data->env);
	data->env = NULL;
	return (err);
}
t_data	*init_data(void)
{
	t_data	*new;

	new = malloc(sizeof(t_data));
	if (!new)
		return (NULL);
	new->pipe_list = NULL;
	new->env = NULL;
	new->exe_path = NULL;
	new->exit_status = 0;
	return (new);
}
