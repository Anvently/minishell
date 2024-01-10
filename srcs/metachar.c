/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:58:46 by npirard           #+#    #+#             */
/*   Updated: 2024/01/09 17:36:16 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <errno.h>

int			expand_var(char *str, t_list **results, char **env);
static int	check_file_meta(t_file_rd *file, char **env);
int			check_files_meta(t_list *files, char **env);

/// @brief Parse given string, removing quotes ("" and '') if necessary
/// and interpret $ sign that need to be interpreted.
/// @param str Unclosed quotes MUST be checked before.
/// @param result pointer toward the head of the list storing the matches
/// of the parsing.
/// @param env Undefined variables are replaced with empty string.
/// @return Number of matches added to ```results```.
/// ```0``` if no match.
/// ```-1``` if allocation error.
int	expand_var(char *str, t_list **results, char **env)
{
	t_list	*words_list;
	int		nbr_match;

	*results = NULL;
	words_list = t_word_parse(str);
	if (!words_list)
		return (-1);
	nbr_match = t_word_interpret(words_list, results, env);
	ft_lstclear(&words_list, t_word_free);
	return (nbr_match);
}

/// @brief Check if given node in a t_file_rd list contain a wildcard in file's
/// path that needs to be interpreted. If so expand it.
/// @param files List of ```t_file_rd``` structure.
/// @return ```0``` if no wildcard was found, if no file was found
/// or if no error occured during wildcard's expension.
/// Set errno to ```1``` if ambiguous redirect.
/// ```-1``` if allocation error (meaning a file was found but path could not be
/// retrieved)
static int	check_file_meta(t_file_rd *file, char **env)
{
	int		nbr_files;
	t_list	*results;

	nbr_files = expand_var(file->path, &results, env);
	if (nbr_files == 0)
		return (0);
	else if (nbr_files < 0)
	{
		free(file->path);
		file->path = NULL;
		return (error(errno, "parsing metacharacters"));
	}
	if (nbr_files > 1)
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
int	check_files_meta(t_list *files, char **env)
{
	t_file_rd	*file;

	while (files)
	{
		file = (t_file_rd *) files->content;
		if (check_file_meta(file, env))
			return (errno);
		files = files->next;
	}
	return (0);
}
