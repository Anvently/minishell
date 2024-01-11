/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:58:46 by npirard           #+#    #+#             */
/*   Updated: 2024/01/11 16:14:11 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <errno.h>

static int	check_file_meta(t_file_rd *file, t_data *data);
int			check_files_meta(t_list *files, t_data *data);

/// @brief Check if given node in a t_file_rd list contain a wildcard in file's
/// path that needs to be interpreted. If so expand it.
/// @param files List of ```t_file_rd``` structure.
/// @return ```0``` if no wildcard was found, if no file was found
/// or if no error occured during wildcard's expension.
/// Set errno to ```1``` if ambiguous redirect.
/// ```errno``` if error
static int	check_file_meta(t_file_rd *file, t_data *data)
{
	t_list	*results;

	if (interpret_metachar(file->path, &results, data))
		return (errno);
	if (ft_lstsize(results) > 1)
	{
		ft_lstclear(&results, NULL);
		return (parse_error(2, file->path));
	}
	free(file->path);
	file->path = ft_strdup((char *) results->content);
	ft_lstclear(&results, NULL);
	if (!file->path)
		return (error(errno, "parsing metacharacters"));
	return (0);
}

/* /// USELESS
/// @brief Check if given file contain a $ sign in its path that needs to be
/// interpreted.
/// @param files List of ```t_file_rd``` structure.
/// @return ```0``` if no wildcard was found or if no error occured during
/// wildcard's expension. Set errno to ```1``` if ambiguous redirect.
static int	check_file_var(t_file_rd *file, char **env)
{

	return (0);
} */

/// @brief Check if given node in a t_file_rd list contain meta characters to
/// interpret in file's path. If so interpret them if necessary.
/// @param files List of ```t_file_rd``` structure.
/// @return ```0``` if no wildcard was found or if no error occured during
/// wildcard's expension. Set errno to ```1``` if ambiguous redirect.
int	check_files_meta(t_list *files, t_data *data)
{
	t_file_rd	*file;

	while (files)
	{
		file = (t_file_rd *) files->content;
		if (check_file_meta(file, data))
			return (errno);
		files = files->next;
	}
	return (0);
}
