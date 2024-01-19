/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:51:01 by npirard           #+#    #+#             */
/*   Updated: 2024/01/19 17:55:11 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <sys/wait.h>

extern int	g_mode;

static void	handle_status(int status, int need_line, t_data *data);
static int	handle_exe_mode(int id, t_data *data);
int			exec_prompt(t_list *pipe_list, t_data *data);

static void	handle_status(int status, int need_line, t_data *data)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == 2)
	{
		data->exit_status = 130;
		write(1, "\n", 1);
		need_line = 0;
	}
	else if (WIFSIGNALED(status) && WTERMSIG(status) == 3)
	{
		data->exit_status = 131;
		ft_putstr_fd("Quit (core dumped)\n", 1);
		need_line = 0;
	}
	else
		data->exit_status = WEXITSTATUS(status);
	if (need_line)
		write(1, "\n", 1);
}

static int	handle_exe_mode(int id, t_data *data)
{
	int	status;
	int	status_other;
	int	need_line;

	status = 0;
	status_other = 0;
	need_line = 0;
	rec_signal();
	waitpid(id, &status, 0);
	while (wait(&status_other) > 0)
	{
		if (WIFSIGNALED(status_other) && WTERMSIG(status_other) == 2)
			need_line = 1;
		status_other = 0;
		continue ;
	}
	if (errno == 10)
		errno = 0;
	handle_status(status, need_line, data);
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
