/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:38:57 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/12 15:05:42 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parse.h>
#include <libft.h>

void	prompt_error(int err, t_data *data, char *str)
{
	if (str)
		free(str);
	free_data(err, data);
	exit (err);
}
/// @brief generate the short hostname and append a : to it
/// @param data

char	*get_hostname(t_data *data)
{
	char	*hostname;
	char	*temp;
	int		len;

	temp = get_var_value("SESSION_MANAGER=local", data->env);
	if (!temp)
		prompt_error(-1, data, NULL);
	len = 0;
	while (temp[len] && temp[len] != '.')
		len++;
	hostname = ft_substr(temp, 0, len);
	free(temp);
	if (!hostname)
		return (NULL);
	temp = ft_strjoin(hostname, ":");
	free(hostname);
	return (temp);
}
/// @brief generate the user@
/// @param data

char	*get_user(t_data *data)
{
	char	*user_name;
	char	*temp;

	temp = get_var_value("USER", data->env);
	if (!temp)
		return (NULL);
	user_name = ft_strjoin(temp, "@");
	free (temp);
	return (user_name);
}

char	*get_pathname(void)
{
	char	*temp;
	char	*path_name;

	temp = getcwd(NULL, 0);
	if (!temp)
		return (NULL);
	path_name = ft_strjoin(temp, "$ ");
	free (temp);
	if (!path_name)
		return (NULL);
	return (path_name);
}

char	*make_prompt(t_data *data)
{
	char	*prompt;
	char	*user_name;
	char	*temp;
	char	*hostname;
	char	*path;

	user_name = get_user(data);
	if (!user_name)
		prompt_error(-1, data, NULL);
	hostname = get_hostname(data);
	if (!hostname)
		prompt_error(-1, data, user_name);
	temp = ft_strjoin(user_name, hostname);
	free(user_name);
	free(hostname);
	if (!temp)
		return (NULL);
	path = get_pathname();
	if (!path)
		prompt_error(-1, data, temp);
	prompt = ft_strjoin(temp, path);
	free(temp);
	free(path);
	return (prompt);
}
