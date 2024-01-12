/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:21:03 by npirard           #+#    #+#             */
/*   Updated: 2024/01/12 19:12:08 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

static void	free_and_exit(int status, char **argv, t_data *data)
{
	ft_free_strs(argv);
	free_data(status, data);
	exit((unsigned char) status);
}

/// @brief Exit current process with given statsus in ```argv[1]```. If an
/// an error occurs during parsing, or too many arguments then
/// exit status is ```1```.
/// @param argv If ```NULL``` or ```argv[0]==NULL```, status is set to ```0```.
void	builtin_exit(char **argv, t_data *data)
{
	int	status;
	int	err;

	if (ft_strslen(argv) > 2)
		free_and_exit(builtin_error(1, "exit", NULL, "too many arguments"),
			argv, data);
	if (!argv || (argv[0] && !argv[1]))
		free_and_exit(data->exit_status, argv, data);
	err = ft_strtoi(argv[1], &status);
	if (!err)
		free_and_exit(status, argv, data);
	else
		free_and_exit(builtin_error(2, "exit", NULL,
				"numeric argument required"), argv, data);
}
