/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:51:01 by npirard           #+#    #+#             */
/*   Updated: 2024/01/03 16:52:43 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

/// @brief Execute a list of ```t_pipe```. First pipe is always executed.
/// Following ones are executed depending on the exit status of previous
/// pipe's last command .
/// @param pipe_list list of ```t_pipe``` structure
/// @param env
/// @return Exit status of last executed command.
/// @note A pipe is defined as such : ```[t_cmd1 | t_cmd2 | t_cmd3]```
/// @note A prompt is defined as such : ```[t_pipe1]([||/&&][t_pipe2]])*n```
int	exec_prompt(t_list *pipe_list, char **env)
{
	int		status;
	t_pipe	*pipe;

	status = 0;
	while (pipe_list)
	{
		pipe = (t_pipe *) pipe_list->content;
		if (pipe->condition == 0 || (!status && pipe->condition == 1)
			|| (status && pipe->condition == 2))
			status = exec_pipe(pipe->commands, env, NULL, 0);
		pipe_list = pipe_list->next;
	}
	return (status);
}
