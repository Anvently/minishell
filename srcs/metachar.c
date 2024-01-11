/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:58:46 by npirard           #+#    #+#             */
/*   Updated: 2024/01/11 15:10:43 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <errno.h>

int	interpret_metachar(char *str, t_list **results, t_data *data);

/// @brief Parse given string, removing quotes ("" and '') if necessary
/// and interpret $ and * that need to be interpreted.
/// @param str Unclosed quotes MUST be checked before.
/// @param result pointer toward the head of the list storing the matches
/// of the parsing.
/// @param env Undefined variables are replaced with empty string.
/// @return ```0``` for success (no match or empty string is a success).
/// ```errno``` if error.
int	interpret_metachar(char *str, t_list **results, t_data *data)
{
	t_list	*word_list;

	*results = NULL;
	if (t_word_parse(str, &word_list, data))
		return (error(errno, "parsing metacharacters"));
	if (word_list && t_word_concat_dup(word_list))
	{
		ft_lstclear(&word_list, t_word_free);
		return (error(errno, "parsing metacharacters"));
	}
	if (word_list && t_word_interpret(word_list, results))
	{
		ft_lstclear(&word_list, t_word_free);
		return (errno);
	}
	ft_lstclear(&word_list, t_word_free);
	return (0);
}
