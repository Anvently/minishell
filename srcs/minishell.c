/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:22:48 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/30 11:35:22 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parse.h>
#include <libft.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

int	g_mode = 0;

int	exe_line(t_data *data, char *line)
{
	int	err;

	err = parse_line(&data->pipe_list, line);
	if (err)
		data->exit_status = err;
	if (err < 0)
		return (-1);
	exec_prompt(data->pipe_list, data);
	ft_lstclear(&data->pipe_list, free_t_pipe);
	return (0);
}

static void	exit_minishell(t_data *data)
{
	ft_putendl_fd("exit", 1);
	exit(free_data(data->exit_status, data));
}

static void	check_signal_exit(t_data *data)
{
	if (errno == 4)
		data->exit_status = 130;
	errno = 0;
}

int	miniline(t_data *data)
{
	char	*line;

	while (1)
	{
		make_prompt(data);
		data->prompt = colorize_prompt(data->prompt);
		if (!data->prompt)
			return (-1);
		line = readline(data->prompt);
		check_signal_exit(data);
		if (line)
			add_history(line);
		else
			exit_minishell(data);
		if (exe_line(data, line))
		{
			free(line);
			ft_lstclear(&data->pipe_list, free_t_pipe);
			return (-1);
		}
		free(line);
		ft_lstclear(&data->pipe_list, free_t_pipe);
		free(data->prompt);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	rec_signal();
	if (init_data(&data, argv, envp) < 0)
		parse_error(-1, NULL);
	if (argc > 1 && exe_line(data, argv[1]))
		return (free_data(-1, data));
	else if (argc < 2 && miniline(data) < 0)
		return (free_data(-1, data));
	return (free_data(data->exit_status, data));
}
