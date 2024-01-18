/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:38:57 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/18 16:40:16 by lmahe            ###   ########.fr       */
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

char	*get_pathname(t_data *data)
{
	char	*path_name;

	path_name = getcwd(NULL, 0);
	if (!path_name)
		return (NULL);
	path_name = replace_with_tilde(path_name, data);
	if (!path_name)
		return (NULL);
	return (path_name);
}

char	*make_prompt(t_data *data)
{
	char	*prompt;
	char	*temp1;
	char	*temp2;
	char	*temp3;

	temp1 = get_user(data);
	if (!temp1)
		prompt_error(-1, data, NULL);
	temp2 = get_hostname(data);
	if (!temp2)
		prompt_error(-1, data, temp1);
	temp3 = ft_strjoin(temp1, temp2);
	free(temp2);
	if (!temp3)
		prompt_error(-1, data, temp1);
	free(temp1);
	temp1 = get_pathname(data);
	if (!temp1)
		prompt_error(-1, data, temp3);
	temp2 = ft_strjoin(temp3, temp1);
	free(temp3);
	free(temp1);
	prompt = ft_strjoin(temp2, "$ ");
	free(temp2);
	return (prompt);
}
