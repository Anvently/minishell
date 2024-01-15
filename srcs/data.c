/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:31:05 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/15 14:47:56 by npirard          ###   ########.fr       */
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
	if (data->exe_path)
		free(data->exe_path);
	if (data->prompt)
		free(data->prompt);
	data->env = NULL;
	free(data);
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
	new->prompt = NULL;
	new->stdin_copy = dup(STDIN_FILENO);
	new->stdout_copy = dup(STDOUT_FILENO);
	if (new->stdin_copy < 0 || new->stdout_copy < 0)
	{
		free_data(-1, new);
		return (NULL);
	}
	new->exit_status = 0;
	return (new);
}
