/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:22:48 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/15 11:59:32 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parse.h>
#include <libft.h>
#include <readline/readline.h>
#include <readline/history.h>

#define CYELLOW "\001\e[0;31m\002"
#define RESET   "\001\e[0m\002


int	is_signal = 0;

int	init_env(t_data **data, char **argv, char **envp)
{
	int	size;
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

int	miniline(t_data *data)
{
	char	*line;
	char	*prompt;

	while (1)
	{
		prompt = make_prompt(data);
		if (!prompt)
			return (-1);
		line = readline(prompt);
		//free(prompt);
		add_history(line);
		if (parse_line(&data->pipe_list, line) < 0)
			return (free(line), -1);
		if (exec_prompt(data->pipe_list, data) < 0)
			return (free(line), -1);
		free(line);
		ft_lstclear(&data->pipe_list, free_t_pipe);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	(void)argc;
	//il faut les sigactions
	if (init_env(&data, argv, envp) < 0)
		parse_error(-1, NULL);

	// if (argc)
	// 	exec_argv(data, argv);
	if (miniline(data) < 0)
		free_data(-1 ,data);




}
