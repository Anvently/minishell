/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:38:57 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/30 11:38:47 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parse.h>
#include <libft.h>

/// @brief generate the short hostname and append a : to it
/// @param data

static bool	is_separator(char c)
{
	if (ft_isalnum(c) || ft_strchr("_-", c))
		return (false);
	return  (true);
}

char	*get_hostname(t_data *data)
{
	char	*hostname;
	char	*temp;
	char	*temp2;
	int		len;

	temp = get_var_value("SESSION_MANAGER", data->env);
	if (!temp)
		return (NULL);
	temp2 = ft_substr(temp, 6, ft_strlen(temp));
	free(temp);
	if (!temp2)
		return (NULL);
	len = 0;
	while (temp2[len] && !is_separator(temp2[len]))
		len++;
	hostname = ft_substr(temp2, 0, len);
	free(temp2);
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

void	make_prompt(t_data *data)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;

	temp1 = get_user(data);
	temp2 = get_hostname(data);
	temp3 = NULL;
	if (temp1 && temp2)
		temp3 = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);
	temp2 = NULL;
	temp1 = get_pathname(data);
	if (temp1 && temp3)
		temp2 = ft_strjoin(temp3, temp1);
	free(temp3);
	free(temp1);
	data->prompt = NULL;
	if (temp2)
		data->prompt = ft_strjoin(temp2, "$ ");
	free(temp2);
	if (!data->prompt)
		data->prompt = ft_strdup("minishell: ");
}
