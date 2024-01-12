/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:22:48 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/12 17:47:58 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parse.h>
#include <libft.h>

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

// int	main(int argc, char **argv, char **envp)
// {
// 	//char	*line;
// 	char	*prompt;
// 	t_data	*data;
// 	(void)argc;
// 	//il faut les sigactions
// 	prompt = NULL;
// 	if (init_env(&data, argv, envp) < 0)
// 		parse_error(-1, NULL);

// 	// if (argc)
// 	// 	exec_argv(data, argv);
// 	prompt = make_prompt(data);
// 	 printf("%s\n", prompt);



// }
