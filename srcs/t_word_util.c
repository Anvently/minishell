/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_word_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:45:02 by npirard           #+#    #+#             */
/*   Updated: 2024/01/09 18:02:40 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

void	t_word_init(t_word *word, char *str, bool quote, char type)
{
	word->content = str;
	word->quote = quote;
	word->type = type;
}

t_list	*t_word_new_node(char *str, bool quote, char type)
{
	t_word	*word;
	t_list	*node;

	word = malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	t_word_init(word, str, quote, type);
	node = ft_lstnew(word);
	if (!node)
		free(word);
	return (node);
}

void	t_word_free(void *word)
{
	if (word)
		free(((t_word *) word)->content);
	free(word);
}

//int		t_word_list_append(t_list **word_list, char *)
