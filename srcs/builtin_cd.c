/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:49:58 by npirard           #+#    #+#             */
/*   Updated: 2024/01/08 17:30:43 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <linux/limits.h>

static int	cd_error(int err, char *path, char *context)
{
	errno = err;
	ft_putstr_fd("minishell: cd: `", 2);
	if (path)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd("': ", 2);
	}
	if (context)
		ft_putendl_fd(context, 2);
	return (err);
}

static char	*find_path(char *path, char **env)
{
	(void) env;
	return (path);
}

/// TODO: only update PWD and OLDPWD if there were declared.
/// TODO: Handle HOME and CDPATH
/// TODO: Check valgrind
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
	char	*path;
	char	oldpwd[PATH_MAX];
	char	newpwd[PATH_MAX];

	if (ft_strslen(argv) > 2)
		return (cd_error(1, NULL, "too many arguments"));
	path = find_path(argv[1], *env);
	if (access(path, F_OK))
		return (cd_error(errno, argv[1], strerror(errno)));
	if (!getcwd(oldpwd, PATH_MAX))
		return (cd_error(errno, NULL, strerror(errno)));
	if (chdir(path))
		return (cd_error(errno, argv[1], strerror(errno)));
	if (!getcwd(newpwd, PATH_MAX))
		return (cd_error(errno, NULL, strerror(errno)));
	if (set_var_value("PWD", newpwd, env))
		return (cd_error(errno, newpwd, "Allocation error when updating PWD"));
	if (set_var_value("OLDPWD", oldpwd, env))
		return (cd_error(errno, oldpwd,
				"Allocation error when updating OLDPWD"));
	return (0);
}
