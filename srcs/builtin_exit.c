/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:21:03 by npirard           #+#    #+#             */
/*   Updated: 2024/01/05 14:17:43 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

/// @brief Exit current process with given statsus in ```argv[1]```. If an
/// an error occurs during parsing, or too many arguments then
/// exit status is ```1```.
/// @param argv If ```NULL``` or ```argv[0]==NULL```, status is set to ```0```.
void	builtin_exit(char **argv)
{
	int	status;
	int	err;

	if (ft_strslen(argv) > 2)
		exit(builtin_error(1, "exit", "too many arguments"));
	if (!argv || (argv[0] && !argv[1]))
		exit(0);
	err = ft_strtoi(argv[1], &status);
	if (!err)
		exit((unsigned char) status);
	else
		exit(builtin_error(2, "exit", "numeric argument required"));
}
