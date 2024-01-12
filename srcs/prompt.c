/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:51:01 by npirard           #+#    #+#             */
/*   Updated: 2024/01/12 18:15:13 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <sys/wait.h>

/// @brief Execute a list of ```t_pipe```. First pipe is always executed.
/// Following ones are executed depending on the exit status of previous
/// pipe's last command .
/// @param pipe_list list of ```t_pipe``` structure
/// @param data
/// @return Exit status of last executed command. data->exit_status
/// is updated whilst executing prompts.
/// @note A pipe is defined as such : ```[t_cmd1 | t_cmd2 | t_cmd3]```
/// @note A prompt is defined as such : ```[t_pipe1]([||/&&][t_pipe2]])*n```
int	exec_prompt(t_list *pipe_list, t_data *data)
{
	int		id;
	int		status;
	t_pipe	*pipe;

	while (pipe_list)
	{
		pipe = (t_pipe *) pipe_list->content;
		if (pipe->condition == 0 || (!data->exit_status
				&& pipe->condition == 1)
			|| (data->exit_status && pipe->condition == 2))
		{
			id = exec_pipe(pipe->commands, data, NULL);
			if (id > 0)
			{
				waitpid(id, &status, 0);
				data->exit_status = status / 256;
				while (wait(NULL) > 0)
					continue ;
			}
			else
				data->exit_status = -id;
		}
		pipe_list = pipe_list->next;
	}
	return (data->exit_status);
}
