/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_word_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:32:58 by npirard           #+#    #+#             */
/*   Updated: 2024/01/18 15:16:12 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

static int	is_void_var(void *word_list);
static int	check_empty_list(t_list **word_list);
int			t_word_parse(char *str, t_list **word_list, t_data *data);
char		*t_word_get_exit_status(char *str, bool quote,
				t_list **word_list, t_data *data);
int			t_word_concat_dup(t_list *word_list);

/// @brief Check if a list node is an empty string variable
/// which was not in quote
/// @param word_list
/// @return
static int	is_void_var(void *word_list)
{
	t_word	*word;

	word = (t_word *)(((t_list *)word_list)->content);
	if (word->type == '$' && word->quote == false
		&& (!word->content || !word->content[0]))
		return (1);
	return (0);
}

/// @brief Check if word list is empty and if so add an empty
/// string. Only case where it can happen is "".
/// @param word_list
/// @return ```0``` for success. ```1``` if error (allocation error).
static int	check_empty_list(t_list **word_list)
{
	t_list	*node;
	char	*str;

	if (!*word_list)
	{
		str = ft_strdup("");
		if (!str)
			return (errno);
		node = t_word_new_node(str, 0, true);
		if (!node)
		{
			free(str);
			return (errno);
		}
		ft_lstadd_back(word_list, node);
	}
	return (0);
}

/// @brief Concatenate litteral word with var word and removing duplicate
/// ```*``` in word_list, leaving only litterals with possible ```*```
/// in between.
/// @param word_list Two consecutive t_word unit with the same type
/// are merged together (* vs litteral/var)
/// @return ```0``` for success ```-1``` for allocation error.
int	t_word_concat_dup(t_list *word_list)
{
	t_word	*word;
	t_word	*word_next;
	t_list	*next;
	char	*new_content;

	while (word_list && word_list->next)
	{
		word = (t_word *)word_list->content;
		word_next = (t_word *)word_list->next->content;
		if ((word->type == '*' && word_next->type == '*')
			|| (word->type != '*' && word_next->type != '*'))
		{
			new_content = ft_strjoin(word->content, word_next->content);
			free(word->content);
			word->content = new_content;
			next = word_list->next->next;
			ft_lstdelone(word_list->next, t_word_free);
			if (!new_content && word->type != '*')
				return (-1);
			word_list->next = next;
		}
		else
			word_list = word_list->next;
	}
	return (0);
}

/// @brief Add a new node to word_list for exit status as a string (case
/// where ```$?``` was given.
/// @param str
/// @param bool
/// @param word_list
/// @param data
/// @return Pointer toward the character following ```?```.
char	*t_word_get_exit_status(char *str, bool quote,
			t_list **word_list, t_data *data)
{
	t_list	*node;

	node = t_word_new_node(ft_itoa(data->exit_status), '$', quote);
	if (!node)
		return (NULL);
	ft_lstadd_back(word_list, node);
	if (!node->content)
		return (NULL);
	return (str + 1);
}

/// @brief Parse given string by splitting it in t_word units (see t_word
/// definition).
/// @param str
/// @param word_list List of t_word used to store result of the parsing
/// @param data
/// @return ```0``` if successfull parsing or empty string.
/// ```-1``` if allocation error.
int	t_word_parse(char *str, t_list **word_list, t_data *data)
{
	bool	quote;

	quote = false;
	*word_list = NULL;
	if (!str || !*str)
		return (0);
	while (str && *str)
	{
		str = t_word_parse_next(str, word_list, &quote, data);
		if (!str)
		{
			ft_lstclear(word_list, t_word_free);
			return (-1);
		}
	}
	if (check_empty_list(word_list))
		return (errno);
	ft_lstdelif(word_list, is_void_var, t_word_free);
	return (0);
}
