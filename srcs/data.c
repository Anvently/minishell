/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:31:05 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/19 12:13:50 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parse.h>
#include <libft.h>
#include <readline/readline.h>
#include <linux/limits.h>

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
	close(data->stdin_copy);
	close(data->stdout_copy);
	rl_clear_history();
	free(data);
	return (err);
}

static t_data	*allocate_data(void)
{
	t_data	*new;

	new = malloc(sizeof(t_data));
	if (!new)
	{
		rl_clear_history();
		return (NULL);
	}
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

static int	init_data_exe_path(t_data *data, char *argv_path)
{
	char	pwd[PATH_MAX];

	if (is_abs_path(argv_path))
	{
		data->exe_path = ft_strdup(argv_path);
		if (!data->exe_path)
			return (errno);
	}
	else if (!getcwd(pwd, PATH_MAX))
		return (errno);
	else
	{
		data->exe_path = ft_strjoin(pwd, argv_path);
		if (!data->exe_path)
			return (errno);
	}
	return (0);
}

int	init_data(t_data **data, char **argv, char **envp)
{
	int		size;

	*data = allocate_data();
	if (!*data)
		return (-1);
	if (init_data_exe_path(*data, argv[0]))
		return (free_data(-1, *data));
	size = ft_strslen(envp);
	(*data)->env = env_copy(envp, size);
	if (!(*data)->env && errno == ENOMEM)
		return (free_data(-1, *data));
	return (0);
}
