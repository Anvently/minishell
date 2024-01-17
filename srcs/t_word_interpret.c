/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_word_interpret.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:49:42 by npirard           #+#    #+#             */
/*   Updated: 2024/01/17 17:24:51 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <errno.h>
#include <unistd.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <dirent.h>

static int	add_default_result(t_list **results, t_list *word_list);
static bool	is_ignored(t_list *word_list, char *path);
int			t_word_interpret(t_list *words, t_list **results);

static int	add_default_result(t_list **results, t_list *word_list)
{
	char	*str;

	str = t_word_concat_str(word_list);
	if (!str)
		return (errno);
	if (ft_lst_str_append(results, str))
	{
		free(str);
		return (errno);
	}
	free(str);
	return (0);
}

/// @brief Check if a hidden file (starting with a ```.```) need to be
/// ignored or not
/// @param word_list
/// @param path
/// @return ```true``` if path is ignored from match else ```false```.
static bool	is_ignored(t_list *word_list, char *path)
{
	t_word	*word;

	if (!word_list)
		return (false);
	word = (t_word *)word_list->content;
	if (path[0] == '.' && (word->type == '*'
			|| (word->type != '*' && word->content[0] != '.')))
		return (true);
	return (false);
}

/// @brief Search for match of t_word units in working directory.
/// @param words Succession of t_word unit of different types (either litterals
/// or ```*```).
/// @param results List of string to store the resulting matches.
/// @return ```0```if no error occured.
/// ```errno``` if error occured.
int	t_word_interpret(t_list *word_list, t_list **results)
{
	char			wk_dir_path[PATH_MAX];
	DIR				*wk_dir;
	struct dirent	*d_file;

	if (!getcwd(wk_dir_path, PATH_MAX))
		return (error(errno, "cannot retrieve working directory path"));
	wk_dir = opendir(wk_dir_path);
	if (!wk_dir)
		return (error(errno, wk_dir_path));
	errno = 0;
	d_file = readdir(wk_dir);
	while (d_file)
	{
		if (!is_ignored(word_list, d_file->d_name)
			&& t_word_match(word_list, d_file->d_name)
			&& ft_lst_str_append(results, d_file->d_name))
			return (closedir(wk_dir), error(errno, d_file->d_name));
		d_file = readdir(wk_dir);
	}
	closedir(wk_dir);
	if (errno)
		return (error(errno, wk_dir_path));
	if (!*results && add_default_result(results, word_list))
		return (error(errno, "trying to concatenate metacharacters"));
	return (0);
}
