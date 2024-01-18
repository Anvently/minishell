/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_word_match.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:49:42 by npirard           #+#    #+#             */
/*   Updated: 2024/01/18 15:57:06 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

static bool	check_wildcard(t_list **word_node, char **path_ptr);
static bool	check_word(t_list **word_node, char **path_ptr);
bool		t_word_match(t_list *word_list, char *path);

static bool	check_wildcard(t_list **word_node, char **path_ptr)
{
	t_word	*word;
	char	*path;

	if (!(*word_node)->next)
	{
		*word_node = (*word_node)->next;
		return (true);
	}
	word = (t_word *)(*word_node)->next->content;
	path = *path_ptr;
	if (!(*word_node)->next->next)
	{
		if (ft_strncmp_rev(path, word->content, ft_strlen(word->content)))
			return (false);
	}
	else
	{
		path = ft_strnstr(path, word->content, ft_strlen(path));
		if (!path)
			return (false);
		path += ft_strlen(word->content);
	}
	*word_node = (*word_node)->next->next;
	*path_ptr = path;
	return (true);
}

static bool	check_word(t_list **word_node, char **path_ptr)
{
	t_word	*word;
	char	*path;

	path = *path_ptr;
	word = (t_word *)(*word_node)->content;
	if ((*word_node)->next
		&& ft_strncmp(word->content, path, ft_strlen(word->content)))
		return (false);
	else if (!(*word_node)->next && ft_strcmp(word->content, path))
		return (false);
	path += ft_strlen(word->content);
	*path_ptr = path;
	*word_node = (*word_node)->next;
	return (true);
}

bool	t_word_match(t_list *word_list, char *path)
{
	t_word	*word;

	while (word_list)
	{
		word = (t_word *) word_list->content;
		if (word->type != '*' && !check_word(&word_list, &path))
			return (false);
		else if (word->type == '*' && !check_wildcard(&word_list, &path))
			return (false);
	}
	return (true);
}

/* /// @brief Check if given path match t_word list.
/// @param words
/// @param str
/// @return ```true```if match else ```false```.
bool	t_word_match(t_list *word_list, char *path)
{
	t_word	*word;
	t_word	*next_word;

	while (word_list)
	{
		word = (t_word *)word_list->content;
		if (word->type == '*' && word_list->next && word->next)
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
} */
