/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:04:34 by npirard           #+#    #+#             */
/*   Updated: 2024/01/15 15:01:15 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <errno.h>

static int	check_name(char *name);
static int	parse_identifier(char *identifier, char **name, char **value);
static int	export_var(char *identifier, char ***env);
int			builtin_export(char **argv, char ***env);

/// @brief Check if the given identifier name has a valid format
/// @param name Name of the variable (before ```=```)
/// @return ```0``` if given identifier is correct.
/// ```1``` if format error.
/// ```-1``` if given name was ```NULL``` (not supposed to happen)
/// @note Name must start with alphabetic character and contain only
/// alphanumeric characters. It must no be empty
/// @note Incorrect format : empty name
static int	check_name(char *name)
{
	if (!name)
		return (-1);
	if (!name[0] || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (1);
	name++;
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (1);
		name++;
	}
	return (0);
}

/// @brief Allocate and assign name and value of given identifier. Check if
/// name has a valid format
/// @param identifier  string in the format NAME=[VALUE].
/// Ignored if no ```=``` is given.
/// @param name Address of string storing var's name
/// @param value Address of string storing var's value. Empty value ([name=])
/// will result in empty string. No equal given will result in ```NULL```.
/// @return ```-1``` if allocation error. No error is printed
/// ```0``` if success or or if no equal given (var will be ignored).
/// ```1``` if format error (no error is printed)
static int	parse_identifier(char *identifier, char **name, char **value)
{
	int	i;

	i = 0;
	while (identifier[i] && identifier[i] != '=')
		i++;
	*name = ft_substr(identifier, 0, i);
	if (*name && check_name(*name))
		return (1);
	else if (!*name)
		return (-1);
	if (!identifier[i++])
		return (0);
	*value = ft_strdup(identifier + i);
	if (!*name || !*value)
		return (-1);
	return (0);
}

/// @brief Take a identifier and add it or update it in env
/// @param identifier String in the format NAME=[VALUE].
/// String is ignored if no ```=``` is given.
/// @param env Address of the environnment pointer
/// @return ```0``` if success or empty string was given.
/// ```-1``` if allocation error (no error is printed)
/// ```1``` if format error (no error is printed).
static int	export_var(char *identifier, char ***env)
{
	char	*name;
	char	*value;
	int		err;

	name = NULL;
	value = NULL;
	err = parse_identifier(identifier, &name, &value);
	if (err < 0)
		return (-1);
	else if (!err && value)
		err = set_var_value(name, value, env);
	if (name)
		free(name);
	if (value)
		free(value);
	return (err);
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
/// ```2``` if allocation error.
int	builtin_export(char **argv, char ***env)
{
	bool	err;
	int		ret;

	err = false;
	if (!argv || !env || ft_strslen(argv) < 2)
		return (0);
	argv++;
	while (*argv)
	{
		ret = export_var(*argv, env);
		if (ret < 0)
			return (builtin_error(2, "export", *argv, "allocation error"));
		else if (ret)
		{
			builtin_error(1, "export", *argv, "not a valid identifier");
			err = true;
		}
		argv++;
	}
	return (err);
}
