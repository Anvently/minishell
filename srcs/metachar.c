/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:58:46 by npirard           #+#    #+#             */
/*   Updated: 2024/01/10 18:57:54 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <errno.h>

int			interpret_metachar(char *str, t_list **results, t_data *data);
static int	check_file_meta(t_file_rd *file, t_data *data);
int			check_files_meta(t_list *files, t_data *data);

/// @brief Parse given string, removing quotes ("" and '') if necessary
/// and interpret $ and * that need to be interpreted.
/// @param str Unclosed quotes MUST be checked before.
/// @param result pointer toward the head of the list storing the matches
/// of the parsing.
/// @param env Undefined variables are replaced with empty string.
/// @return ```0``` for success (no match or empty string is a success).
/// ```errno``` if error.
int	interpret_metachar(char *str, t_list **results, t_data *data)
{
	t_list	*word_list;

	*results = NULL;
	if (t_word_parse(str, &word_list, data))
		return (error(errno, "parsing metacharacters"));
	if (word_list && t_word_concat_dup(word_list))
	{
		ft_lstclear(&word_list, t_word_free);
		return (error(errno, "parsing metacharacters"));
	}
	if (word_list && t_word_interpret(word_list, results))
	{
		ft_lstclear(&word_list, t_word_free);
		return (error(errno, "interpreting wildcards"));
	}
	ft_lstclear(&word_list, t_word_free);
	return (0);
}

/// @brief Check if given node in a t_file_rd list contain a wildcard in file's
/// path that needs to be interpreted. If so expand it.
/// @param files List of ```t_file_rd``` structure.
/// @return ```0``` if no wildcard was found, if no file was found
/// or if no error occured during wildcard's expension.
/// Set errno to ```1``` if ambiguous redirect.
/// ```errno``` if error
static int	check_file_meta(t_file_rd *file, t_data *data)
{
	int		nbr_files;
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
		if (check_file_meta(file, data->env))
			return (errno);
		files = files->next;
	}
	return (0);
}
