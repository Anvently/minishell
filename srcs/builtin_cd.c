/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:49:58 by npirard           #+#    #+#             */
/*   Updated: 2024/01/30 11:49:01 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <linux/limits.h>

/// @brief Execute chdir after looking for path
/// @param path
/// @param env
/// @return ```0``` for success.
/// ```errno``` for error.
static int	exec_cd(char *path, char **env)
{
	char	*tmp_path;

	tmp_path = NULL;
	if (cd_find_path(&tmp_path, path, env))
	{
		if (tmp_path)
			free(tmp_path);
		return (errno);
	}
	if (tmp_path && tmp_path[0] && chdir(tmp_path))
	{
		free(tmp_path);
		return (builtin_error(errno, "cdr", path, strerror(errno)));
	}
	free(tmp_path);
	return (0);
}

/// @brief Update env with oldpwd and newpwd. Env will not be updated
/// for NULL variable
/// @param oldpwd
/// @param newpwd
/// @param env
/// @return ```0``` for success. ```errno``` for error.
static int	update_env(char *oldpwd, char *newpwd, char ***env)
{
	if (oldpwd[0] && set_var_value("OLDPWD", oldpwd, env))
		return (builtin_error(2, "cd", "OLDPWD", "allocation error"));
	if (newpwd[0] && set_var_value("PWD", newpwd, env))
		return (builtin_error(2, "cd", "PWD", "allocation error"));
	return (0);
}

/// @brief For a given string address, check if a variable given by ```name```
/// is defined in env and if so, store current working directory in string
/// address.
/// If variable is not defined, value of string is left to ```NULL```.
/// @param pwd
/// @param name
/// @param env
/// @return ```0``` for success or nothing to be done.
/// ```errno``` if error occured (for getcwd)
static int	update_pwd(char *pwd, char *name, char **env)
{
	if (!pwd)
		return (0);
	if (is_var_defined(name, env))
		if (!getcwd(pwd, PATH_MAX))
			return (builtin_error(errno, "cd", name, strerror(errno)));
	return (0);
}

/// @brief Change current working directory
/// @param argv Accept only 0 (path=HOME) or 1 (relative or absolute path)
///  argument.
/// @param env ```PWD``` and ```OLDPWD``` are updated ONLY if they are declared.
/// ```HOME``` defines behaviour of cd when no argument is given.
/// ```CDPATH``` add search path to the list (in addition of working directory).
/// @return ```0``` for success.
/// ```1``` for error (too many argument, wrong path, home not set)
/// ```2``` for allocation error
int	builtin_cd(char **argv, char ***env)
{
	char	oldpwd[PATH_MAX];
	char	newpwd[PATH_MAX];

	oldpwd[0] = '\0';
	newpwd[0] = '\0';
	if (ft_strslen(argv) > 2)
		return (builtin_error(1, "cd", NULL, "too many arguments"));
	if (update_pwd(&oldpwd[0], "OLDPWD", *env))
		return (errno);
	if (exec_cd(argv[1], *env))
		return (errno);
	if (update_pwd(&newpwd[0], "PWD", *env))
		return (errno);
	if (update_env(oldpwd, newpwd, env))
		return (errno);
	return (0);
}
