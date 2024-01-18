/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:06:33 by npirard           #+#    #+#             */
/*   Updated: 2024/01/18 16:27:30 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <errno.h>

static char	*var_join(char const *var, char const *value);
char		*get_var_value(char *var, char **env);
char		**env_copy(char **env, int size);
static int	add_var_value(char ***env, char *var);
int			set_var_value(char *var, char *value, char ***env);

/// @brief Concatenate var and value, adding a ```=``` in between
/// @param var
/// @param value Can be ```NULL```
/// @return Address of new allocated string. ```NULL``` if allocation error.
static char	*var_join(char const *var, char const *value)
{
	char	*buffer;
	size_t	size;
	size_t	len_var;
	size_t	len_value;

	len_var = ft_strlen(var);
	if (!value)
		len_value = 0;
	else
		len_value = ft_strlen(value);
	size = len_var + len_value + 2;
	buffer = malloc(size);
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, var, size);
	buffer[len_var] = '=';
	buffer[len_var + 1] = '\0';
	ft_strlcat(buffer, value, size);
	return (buffer);
}

/// @brief Look for a given variable in env and return it as a new allocated
/// string
/// @param var Name of the variable to find (without $)
/// @param env
/// @return Allocated string. If variable isn't found, return empty string.
/// ```NULL``` if allocation error.
char	*get_var_value(char *var, char **env)
{
	char	*var_value;
	size_t	len_var;

	if (!var)
		return (NULL);
	len_var = ft_strlen(var);
	while (*env)
	{
		if (!ft_strncmp(*env, var, len_var))
			if ((*env)[len_var] == '=')
				break ;
		env++;
	}
	if (*env)
		var_value = ft_substr(*env, len_var + 1,
				ft_strlen(*env) - len_var + 1);
	else
		var_value = ft_strdup("");
	if (!var_value)
		return (alloc_error());
	return (var_value);
}

/// @brief Return a new list of string which is a copy of env.
/// If size > size(env), ```NULL``` are added to the full size of
/// the new env.
/// @param env
/// @param size size of the new environnement to create (not including
/// terminating NULL).
/// @return Adress of new env. If allocation fails return ```NULL```.
char	**env_copy(char **env, int size)
{
	char	**new_env;
	int		i;

	new_env = malloc((size + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	new_env[size] = NULL;
	i = 0;
	while (env && i < size && env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (ft_free_strs(new_env));
		i++;
	}
	while (i < size)
		new_env[i++] = NULL;
	return (new_env);
}

/// @brief Add a new variable entry to env
/// @param env it is freed and reallocated in the process.
/// @param var variable entry in the format of ```NAME=[VALUE]```.
/// @return ```0``` if succes (env is updated)
/// ```-1``` if allocation error (current env is left untouched)
static int	add_var_value(char ***env, char *var)
{
	char	**new_env;
	int		size_env;

	size_env = ft_strslen(*env);
	new_env = env_copy(*env, size_env + 1);
	if (!new_env)
	{
		free(var);
		return (error(-1, "adding variable in env"));
	}
	new_env[size_env] = var;
	ft_free_strs(*env);
	*env = new_env;
	return (0);
}

/// @brief Add var to env or update it if already existing.
/// @param var
/// @param value Can be ```NULL```.
/// @param env
/// @return ```0``` if success.
/// ```-1``` if allocation error. Error is not printed
int	set_var_value(char *var, char *value, char ***env)
{
	size_t	len_var;
	char	*new_var;
	char	**env_ptr;

	new_var = var_join(var, value);
	env_ptr = *env;
	if (!*new_var)
		return (-1);
	len_var = ft_strlen(var);
	while (*env_ptr && ft_strncmp(*env_ptr, var, len_var))
		env_ptr++;
	if (*env_ptr)
	{
		free(*env_ptr);
		*env_ptr = new_var;
	}
	else if (add_var_value(env, new_var))
		return (-1);
	return (0);
}

