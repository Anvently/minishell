/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_word_interpret.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:49:42 by npirard           #+#    #+#             */
/*   Updated: 2024/01/18 15:50:24 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <errno.h>
#include <unistd.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <dirent.h>

static int	check_word_list(t_list **results, t_list *word_list);
static int	add_default_result(t_list **results, t_list *word_list);
static bool	is_ignored(t_list *word_list, char *path);
static int	find_matches(DIR *wk_dir, t_list **results, t_list *word_list);
int			t_word_interpret(t_list *words, t_list **results);

/// @brief Check if word_list is only composed of an empty string, or if it
/// doesn't contain metacharacters (in which case word_list is concatenated).
/// In this case an empty string is added to ```resutls``` list.
/// @param results
/// @param word_list
/// @return ```0``` if word_list contain metacharacters
/// ```1``` if error or if it was only an empty string (and was successfully)
/// added to results. If error, ```errno``` is set to error code.
static int	check_word_list(t_list **results, t_list *word_list)
{
	t_word	*word;

	word = (t_word *)word_list->content;
	if ((!word_list || !word_list->next) && word->type != '*'
		&& word->content[0] == '\0')
	{
		ft_lst_str_append(results, "");
		return (1);
	}
	else if (ft_lstsize(word_list) == 1 && word->type != '*')
	{
		add_default_result(results, word_list);
		return (1);
	}
	return (0);
}

/// @brief Add a concatenation of word_list to result list.
/// @param results
/// @param word_list
/// @return ```0``` for success.
/// ```errno``` if error (allocation error)
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

/// @brief Search for match of t_word units in given directory.
/// @param wk_dir
/// @param results List of string to store the resulting matches.
/// @param word_list Succession of t_word unit of different types
/// (either litterals or ```*```).
/// @return ```0``` for success. ```errno``` if error.
static int	find_matches(DIR *wk_dir, t_list **results, t_list *word_list)
{
	struct dirent	*d_file;

	d_file = readdir(wk_dir);
	errno = 0;
	while (d_file)
	{
		if (!is_ignored(word_list, d_file->d_name)
			&& t_word_match(word_list, d_file->d_name)
			&& ft_lst_str_append(results, d_file->d_name))
			return (error(errno, d_file->d_name));
		d_file = readdir(wk_dir);
	}
	if (errno)
		return (error(errno, d_file->d_name));
	return (0);
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

	errno = 0;
	if (check_word_list(results, word_list))
	{
		if (errno)
			return (error(errno, "checking for metacharacters"));
		return (0);
	}
	if (!getcwd(wk_dir_path, PATH_MAX))
		return (error(errno, "cannot retrieve working directory path"));
	wk_dir = opendir(wk_dir_path);
	if (!wk_dir)
		return (error(errno, wk_dir_path));
	find_matches(wk_dir, results, word_list);
	closedir(wk_dir);
	if (errno)
		return (errno);
	if (!*results && add_default_result(results, word_list))
		return (error(errno, "trying to concatenate metacharacters"));
	return (0);
}
