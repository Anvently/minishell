/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_word_interpret.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:49:42 by npirard           #+#    #+#             */
/*   Updated: 2024/01/17 15:33:57 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <errno.h>
#include <unistd.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <dirent.h>

static bool	is_match(t_list *word_list, char *path);
static int	add_default_result(t_list **results, t_list *word_list);
static bool	is_ignored(t_list *word_list, char *path);
int			t_word_interpret(t_list *words, t_list **results);

/// @brief Check if given path match t_word list.
/// @param words
/// @param str
/// @return ```true```if match else ```false```.
static bool	is_match(t_list *word_list, char *path)
{
	t_word	*word;
	t_word	*next_word;

	while (word_list)
	{
		word = (t_word *)word_list->content;
		if (word->type == '*' && word_list->next)
		{
			next_word = ((t_word *)word_list->next->content);
			path = ft_strnstr(path, next_word->content, ft_strlen(path));
			if (!path)
				return (false);
			path += ft_strlen(next_word->content);
			word_list = word_list->next;
			word = (t_word *)word_list->content;
		}
		else if (word->type != '*')
		{
			if (ft_strncmp(word->content, path, ft_strlen(word->content)))
				return (false);
			path += ft_strlen(word->content);
		}
		word_list = word_list->next;
	}
	return ((word->type != '*' && !*path) || word->type == '*');
}

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
			&& is_match(word_list, d_file->d_name)
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
