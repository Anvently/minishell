/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_word_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:45:02 by npirard           #+#    #+#             */
/*   Updated: 2024/01/17 18:02:21 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

void	t_word_init(t_word *word, char *str, char type, bool quote);
t_list	*t_word_new_node(char *str, char type, bool quote);
void	t_word_free(void *word);
void	t_word_print(void *content);
char	*t_word_concat_str(t_list *word_list);

void	t_word_init(t_word *word, char *str, char type, bool quote)
{
	word->content = str;
	word->type = type;
	word->quote = quote;
}

t_list	*t_word_new_node(char *str, char type, bool quote)
{
	t_word	*word;
	t_list	*node;

	word = malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	t_word_init(word, str, type, quote);
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

void	t_word_print(void *content)
{
	t_word	*word;

	word = (t_word *)content;
	printf("content = %s | type = %c | quote = %d\n",
		word->content, word->type, word->quote);
}

/// @brief Return the concatenation of every word in word_list
/// @param word_list
/// @return Allocated string. ```NULL``` if allocation error or if
/// word_list is empty.
char	*t_word_concat_str(t_list *word_list)
{
	char	*str_tmp;
	char	*str;
	t_word	*word;

	str = NULL;
	while (word_list)
	{
		word = (t_word *)word_list->content;
		if (word->type != '*')
			str_tmp = ft_strjoin2(str, (char *)word->content);
		else if (word->type == '*')
			str_tmp = ft_strjoin2(str, "*");
		free(str);
		if (!str_tmp)
			return (NULL);
		str = str_tmp;
		word_list = word_list->next;
	}
	return (str);
}
