/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_word_interpret.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:49:42 by npirard           #+#    #+#             */
/*   Updated: 2024/01/11 10:33:22 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <errno.h>
#include <unistd.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <dirent.h>

static int	append_result(t_list **results, char *str);
static bool	is_match(t_list *word_list, char *path);
int			t_word_interpret(t_list *words, t_list **results);

/// @brief Append a str to the list of result.
/// @param results
/// @param str
/// @return ```0``` for success.
/// ```-1``` if allocation error, list is freed.
static int	append_result(t_list **results, char *str)
{
	t_list	*node;
	char	*content;

	content = ft_strdup(str);
	if (!content)
	{
		ft_lstclear(results, free);
		return (-1);
	}
	node = ft_lstnew(content);
	if (!node)
	{
		free(content);
		ft_lstclear(results, free);
		return (-1);
	}
	ft_lstadd_back(results, node);
	return (0);
}

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
			next_word = (t_word *)word_list->next->content;
			path = ft_strnstr(path, next_word->content, ft_strlen(path));
			if (!path)
				return (false);
			path += ft_strlen(next_word->content);
			word_list = word_list->next;
		}
		else if (word->type != '*')
		{
			if (ft_strncmp(word->content, path, ft_strlen(word->content)))
				return (false);
			path += ft_strlen(word->content);
		}
		word_list = word_list->next;
	}
	return (true);
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

	if (!word_list->next && ((t_word *)word_list->content)->type != '*')
		if (append_result(results, ((t_word *)word_list->content)->content))
			return (error(errno, "interpreting metacharacters"));
	if (!getcwd(wk_dir_path, PATH_MAX))
		return (error(errno, "cannot retrieve working directory path"));
	wk_dir = opendir(wk_dir_path);
	if (!opendir)
		return (error(errno, wk_dir_path));
	errno = 0;
	d_file = readdir(wk_dir);
	while (d_file)
	{
		if (is_match(word_list, d_file->d_name)
			&& append_result(results, d_file->d_name))
			return (error(errno, d_file->d_name));
		d_file = readdir(wk_dir);
	}
	if (errno)
		return (error(errno, wk_dir_path));
	return (0);
}
