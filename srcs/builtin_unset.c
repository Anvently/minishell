/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:54:59 by npirard           #+#    #+#             */
/*   Updated: 2024/01/09 09:54:41 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

static bool	check_filter(char *entry, char **filter);
static char	**env_filter_copy(char **env, char **filter);
int			builtin_unset(char **argv, char ***env);


/// @brief Check filter list contains given entry's name.
/// @param entry String in the format NAME=[VALUE]
/// @param filter List of variables name.
/// @return ```true``` if entry is in filter list.
static bool	check_filter(char *entry, char **filter)
{
	int		i;

	i = 0;
	while (entry[i] != '=')
		i++;
	while (filter && *filter)
	{
		if (!ft_strncmp(entry, *filter, i))
			return (true);
		filter++;
	}
	return (false);
}

/// @brief Return a new list of string which is a copy of env where all
/// variable name's contained within filter are ignored.
/// @param env Environment to copy.
/// @param filter List of variable to remove from env. Can be ```NULL```
/// @return Adress of new env. If allocation fails return ```NULL```.
/// @note New env will have the same size than old env. The number of
/// terminating ```NULL``` will be equal to the number of removed variable
/// + 1 for the default terminating ```NULL```.
static char	**env_filter_copy(char **env, char **filter)
{
	char	**new_env;
	int		size_env;
	int		i;

	size_env = ft_strslen(env);
	new_env = malloc((size_env + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	new_env[size_env] = NULL;
	i = 0;
	while (env && i < size_env && *env)
	{
		if (!check_filter(*env, filter))
		{
			new_env[i] = ft_strdup(*env);
			if (!new_env[i])
				return (ft_free_strs(new_env));
			i++;
		}
		env++;
	}
	while (i < size_env)
		new_env[i++] = NULL;
	return (new_env);
}

/// @brief Remove a variable entry from environment.
/// @param argv each argument is a variable to unset. A non-declared variable
/// will be ignored.
/// @param env environment is reallocated.
/// @return ```0``` for success.
/// ```2``` if allocation error.
int	builtin_unset(char **argv, char ***env)
{
	char	**new_env;

	if (argv[1])
	{
		new_env = env_filter_copy(*env, argv + 1);
		if (!new_env)
			return (builtin_error(2, "unset", NULL, "allocation error"));
		ft_free_strs(*env);
		*env = new_env;
	}
	return (0);
}
