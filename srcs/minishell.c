/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:22:48 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/16 11:41:05 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parse.h>
#include <libft.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

int	g_mode = 0;

int	init_env(t_data **data, char **argv, char **envp)
{
	int		size;
	char	*pwd;

	*data = init_data();
	if (!*data)
		return (-1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free_data(-1, *data));
	(*data)->exe_path = path_join(pwd, argv[0]);
	free(pwd);
	if (!(*data)->exe_path)
		return (free_data(-1, *data));
	size = ft_strslen(envp);
	(*data)->env = env_copy(envp, size);
	if (!(*data)->env && errno == ENOMEM)
		return (free_data(-1, *data));
	return (0);
}

int	exe_line(t_data *data, char *line)
{
	if (parse_line(&data->pipe_list, line) < 0)
		return (-1);
	exec_prompt(data->pipe_list, data);
	ft_lstclear(&data->pipe_list, free_t_pipe);
	return (0);
}

static void	exit_minishell(t_data *data)
{
	ft_putendl_fd("exit", 1);
	exit(free_data(0, data));
}

int	miniline(t_data *data)
{
	char	*line;

	while (1)
	{
		data->prompt = make_prompt(data);
		data->prompt = colorize_prompt(data->prompt);
		if (!data->prompt)
			return (-1);
		line = readline(data->prompt);
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
		//golbal = 0
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	printf("PID=%d\n",getpid());
	rec_signal();
	if (init_env(&data, argv, envp) < 0)
		parse_error(-1, NULL);
	if (argc > 1 && exe_line(data, argv[1]))
		return (free_data(-1, data));
	else if (argc < 2 && miniline(data) < 0)
		return (free_data(-1, data));
	return (free_data(data->exit_status, data));
}
