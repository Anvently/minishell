/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:58:46 by npirard           #+#    #+#             */
/*   Updated: 2024/01/04 17:09:20 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <errno.h>

/// @brief Check if given node in a t_file_rd list contain a wildcard in file's
/// path. If so expand it.
/// @param files List of ```t_file_rd``` structure.
/// @return ```0``` if no wildcard was found or if no error occured during
/// wildcard's expension. Set errno to ```1``` if ambiguous redirect.
static int	check_file_wc(t_file_rd *file)
{

	return (0);
}

/// @brief Check if given file contain a $ sign in its path that needs to be
/// interpreted.
/// @param files List of ```t_file_rd``` structure.
/// @return ```0``` if no wildcard was found or if no error occured during
/// wildcard's expension. Set errno to ```1``` if ambiguous redirect.
static int	check_file_var(t_file_rd *file, char **env)
{

	return (0);
}

/// @brief Check if given node in a t_file_rd list contain meta characters to
/// interpret in file's path. If so interpret them
/// @param files List of ```t_file_rd``` structure.
/// @return ```0``` if no wildcard was found or if no error occured during
/// wildcard's expension. Set errno to ```1``` if ambiguous redirect.
int	check_file_meta(t_list *files, char **env)
{
	t_file_rd	*file;

	while (files)
	{
		file = (t_file_rd *) files->content;
		check_file_var(file, env);
		if (check_file_wc(file))
			return (errno);
		files = files->next;
	}
	return (0);
}
