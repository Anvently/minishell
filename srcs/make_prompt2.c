/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_prompt2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:44:08 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/19 11:16:52 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

char	*remove_home(char *path, char *home, char *find)
{
	int	i;
	int	j;

	j = ft_strlen(home);
	i = 1;
	find[0] = '~';
	find[1] = '/';
	while (find[i + j])
	{
		find[i + 1] = find[i + j];
		i++;
	}
	find[i + 1] = 0;
	free(home);
	return (path);
}

char	*replace_with_tilde(char *path, t_data *data)
{
	char	*user;
	char	*home;
	char	*res;

	user = get_var_value("USER", data->env);
	if (!user)
		return (NULL);
	home = ft_strjoin("/home/", user);
	free(user);
	if (!home)
		return (NULL);
	user = ft_strnstr(path, home, ft_strlen(path));
	if (!user)
	{
		free(home);
		return (path);
	}
	path = remove_home(path, home, user);
	res = ft_strdup(path);
	free(path);
	return (res);
}

char	*colorize_prompt(char *prompt)
{
	char	*buffer1;
	char	*buffer2;

	if (!prompt)
		return (NULL);
	buffer1 = ft_strjoin(COLOR_YELLOW, prompt);
	free(prompt);
	if (!buffer1)
		return (NULL);
	buffer2 = ft_strjoin(buffer1, COLOR_RESET);
	free(buffer1);
	if (!buffer2)
		return (NULL);
	return (buffer2);
}
