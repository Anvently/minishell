/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:37:42 by npirard           #+#    #+#             */
/*   Updated: 2024/01/12 13:43:04 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

static void	catch_signal(int signo)
{
	printf("SIGNAL CATCHED : %d\n", signo);
}

int	main(int argc, char **argv, char **env)
{
	char	**strs;
	char	*line;
	t_data	data;

	(void) argc;
	signal(SIGINT, catch_signal);
	data.exit_status = 0;
	data.exe_path = ft_strdup(argv[0]);
	if (!data.exe_path)
		exit(1);
	data.env = env_copy(env, ft_strslen(env));
	if (!data.env)
		return (-1);
	while ((line = readline("minishell: ")))
	{
		add_history(line);
		strs = ft_split(line, ' ');
		if (!strs) {
			free(line);
			return (-1);
		}
		if (update_argv(&strs, &data))
		{
			free(line);
			free_data(0, &data);
			rl_clear_history();
			ft_free_strs(strs);
			exit(errno);
		}
		if (!ft_strcmp(strs[0], "export"))
			printf("status = %d\n", builtin_export(strs, &data.env));
		else if (!ft_strcmp(strs[0], "env"))
			printf("status = %d\n", builtin_env(data.env));
		else if (!ft_strcmp(strs[0], "echo"))
			printf("status = %d\n", builtin_echo(strs));
		else if (!ft_strcmp(strs[0], "exit"))
		{
			free(line);
			free_data(0, &data);
			rl_clear_history();
			builtin_exit(strs);
		}
		else if (!ft_strcmp(strs[0], "unset"))
			printf("status = %d\n", builtin_unset(strs, &data.env));
		else if (!ft_strcmp(strs[0], "pwd"))
			printf("status = %d\n", builtin_pwd());
		else if (!ft_strcmp(strs[0], "cd"))
			printf("status = %d\n", builtin_cd(strs, &data.env));
		free(line);
		ft_free_strs(strs);
	}
	return (free_data(0, &data));
}
