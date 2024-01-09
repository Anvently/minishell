/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:21:03 by npirard           #+#    #+#             */
/*   Updated: 2024/01/09 09:59:31 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

static void	free_and_exit(int status, char **argv)
{
	ft_free_strs(argv);
	exit(status);
}

/// @brief Exit current process with given statsus in ```argv[1]```. If an
/// an error occurs during parsing, or too many arguments then
/// exit status is ```1```.
/// @param argv If ```NULL``` or ```argv[0]==NULL```, status is set to ```0```.
void	builtin_exit(char **argv)
{
	int	status;
	int	err;

	if (ft_strslen(argv) > 2)
		free_and_exit(builtin_error(1, "exit", NULL, "too many arguments"),
			argv);
	if (!argv || (argv[0] && !argv[1]))
		free_and_exit(0, argv);
	err = ft_strtoi(argv[1], &status);
	if (!err)
		free_and_exit((unsigned char) status, argv);
	else
		free_and_exit(builtin_error(2, "exit", NULL,
				"numeric argument required"), argv);
}
