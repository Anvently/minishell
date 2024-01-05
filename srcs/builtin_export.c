/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:04:34 by npirard           #+#    #+#             */
/*   Updated: 2024/01/05 18:02:45 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <errno.h>

static int	error_export(int err, char *identifier, char *context)
{
	errno = err;
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("': ", 2);
	if (context)
		ft_putendl_fd(context, 2);
	return (err);
}

/// @brief Check if the given
/// @param str
/// @return
static int	check_identifier(char *identifier, char *name)
{
	if (!name)
		return (-1);
	if (!name[0])
		return (error_export(1, identifier, "not a valid identifier"));
	//Need to check other stuff.
}

static char	*parse_name(char *str, char **name)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	*name = ft_substr(str, 0, i);
	if (!name)
		alloc_error();
	return (str + i);
}

static int	export_var(char *identifier, char ***env)
{
	char	*name;
	char	*value;
	char	*str;

	str = identifier;
	str = parse_name(str, &name);
	if (!name)
		return (-1);
	if (check_identifier(identifier, name))
		return (1);
	if (!*(str++))
		return (0);
	value = ft_strdup(str);
	if (!value)
	{
		alloc_error();
		return (-1);
	}
	return (set_var_value(name, value, env));
}

/// @brief Define or update the value of an environnement variable
/// @param argv 0, 1 or more string in the format NAME[=[VALUE]].
/// @note If format : NAME => ignored
/// @note If format : NAME= => declared but value left blank
/// @note If format : NAME=VALUE => set to value
/// @note Name must start with alphabetic character and contain only
/// alphanumeric characters. It must no be empty
/// @note Incorrect format : empty name
/// @param env
/// @return ```0``` if no error occured for every argument.
/// ```1``` if a least one of the export failed.
int	builtin_export(char **argv, char ***env)
{
	if (!argv || !env || ft_strslen(argv) < 2)
		return (0);
	argv++;
	while (*argv)
	{

		argv++;
	}
	return (0);
}
