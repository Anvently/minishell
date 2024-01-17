/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:51:01 by npirard           #+#    #+#             */
/*   Updated: 2024/01/17 12:12:33 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <sys/wait.h>

extern int	g_mode;

int	handle_exe_mode(int id, t_data *data);
int	exec_prompt(t_list *pipe_list, t_data *data);

int	handle_exe_mode(int id, t_data *data)
{
	int	status;

	status = 0;
	rec_signal();
	waitpid(id, &status, 0);
	data->exit_status = WEXITSTATUS(status);
	while (wait(NULL) > 0)
		continue ;
	if (errno == 10)
		errno = 0;
	if (WIFSIGNALED(status) && WTERMSIG(status) == 2)
		write(1, "\n", 1);
	if (WIFSIGNALED(status) && WTERMSIG(status) == 3)
		ft_putstr_fd("Quit (core dumped)\n", 1);
	g_mode = 0;
	rec_signal();
	return (0);
}

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
	t_pipe	*pipe;

	while (pipe_list)
	{
		pipe = (t_pipe *) pipe_list->content;
		if (pipe->condition == 0 || (!data->exit_status && pipe->condition == 1)
			|| (data->exit_status && pipe->condition == 2))
		{
			id = exec_pipe(pipe->commands, data, NULL);
			if (id > 0)
				handle_exe_mode(id, data);
			else
				data->exit_status = -id;
		}
		pipe_list = pipe_list->next;
	}
	return (data->exit_status);
}
