/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_word_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:32:58 by npirard           #+#    #+#             */
/*   Updated: 2024/01/09 18:12:21 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

int		t_word_interpret(t_list *words, t_list **results, char **env);
t_list	*t_word_parse(char *str);

/// @brief Add a new node containing everything between str[0] and the next
/// ```'``` character.
/// @param str
/// @param word_list
/// @return Address of the character following the next ```'``` found,
/// or ```NULL``` if allocation error.
static char	*get_simple_quote(char *str, t_list **word_list)
{
	t_list	*node;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\'')
		i++;
	if (str[i])
	{
		node = t_word_new_node(ft_substr(str, 0, i - 1), false, 0);
		if (!node)
			return (NULL);
		ft_lstadd_back(word_list, node);
		if (!node->content)
			return (NULL);
		return (str + i + 1);
	}
	return (str + i);
}

static char	*find_next_word(char *str, t_list **word_list, bool *quote)
{
	int	i;

	if (!*quote && *str == '\'')
		str = get_quote(str, &word_list);
	else if (str && *str == '"')
	{
		*quote = !*quote;
		str++;
	}
	while (str && *str && !ft_strchr("\" $", *str))


	return (str);
}

t_list	*t_word_parse(char *str)
{
	t_list	*word_list;
	bool	quote;

	quote = false;
	while (str && *str)
	{
		str = find_next_word(str, &word_list, &quote);
		if (!str)
			ft_lstclear(&word_list, t_word_free);
	}
	return (word_list);
}
