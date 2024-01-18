/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_word_parsing2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:32:58 by npirard           #+#    #+#             */
/*   Updated: 2024/01/17 18:08:44 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

static char	*get_simple_quote(char *str, bool quote, t_list **word_list);
static char	*get_var_string(char *str, bool quote,
				t_list **word_list, t_data *data);
static char	*get_wc_string(char *str, bool quote, t_list **word_list);
static char	*get_word_string(char *str, t_list **word_list, bool quote);
char		*t_word_parse_next(char *str, t_list **word_list, bool *quote,
				t_data *data);

/// @brief Add a new node containing everything between str[0] and the next
/// ```'``` character.
/// @param str
/// @param word_list
/// @return Address of the character following the next ```'``` found,
/// or ```NULL``` if allocation error.
static char	*get_simple_quote(char *str, bool quote, t_list **word_list)
{
	t_list	*node;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\'')
		i++;
	if (i == 0)
		return (str + i);
	node = t_word_new_node(ft_substr(str, 0, i), 0, quote);
	if (!node)
		return (NULL);
	ft_lstadd_back(word_list, node);
	if (!node->content)
		return (NULL);
	if (str[i])
		return (str + i + 1);
	return (str + i);
}

/// @brief Add a new node containing the value of the variable parsed (which
/// name is defined by a succesion of alphanumeric characters)
/// @param str
/// @param word_list
/// @return Address of the first non alphanumeric character found,
/// or ```NULL``` if allocation error.
static char	*get_var_string(char *str, bool quote,
				t_list **word_list, t_data *data)
{
	t_list	*node;
	char	*var_name;
	int		i;

	i = 0;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	var_name = ft_substr(str, 0, i);
	if (!var_name)
		return (NULL);
	node = t_word_new_node(get_var_value(var_name, data->env), '$', quote);
	free(var_name);
	if (!node)
		return (NULL);
	ft_lstadd_back(word_list, node);
	if (!node->content)
		return (NULL);
	return (str + i);
}

/// @brief Add a ```*``` node to word_list
/// @param str
/// @param word_list
/// @return pointer toward next character or ```NULL``` if allocation
/// error.
static char	*get_wc_string(char *str, bool quote, t_list **word_list)
{
	t_list	*node;

	node = t_word_new_node(NULL, '*', quote);
	if (!node)
		return (NULL);
	ft_lstadd_back(word_list, node);
	return (str + 1);
}

/// @brief Add a new node containing the next word found.
/// Definition of a word depends on the status of quote.
/// If inside quote (""), words will end with ```"``` or with ```$```
/// (only if defining a variable).
/// If outside quote, words will end with one of the following character
/// ```'*"``` or with a ```$``` (only if defining a variable).
/// @param str
/// @param word_list
/// @param quote
/// @return Address of the character following the next word found,
/// or ```NULL``` if allocation error.
static char	*get_word_string(char *str, t_list **word_list, bool quote)
{
	t_list	*node;
	int		i;

	i = 0;
	while (str[i]
		&& !((quote == true && ft_strchr("\"", str[i]))
			|| (quote == false && ft_strchr("'*\"", str[i]))
			|| (str[i] == '$' && (ft_isalnum(str[i + 1])
					|| str[i + 1] == '?'))))
		i++;
	node = t_word_new_node(ft_substr(str, 0, i), 0, quote);
	if (!node)
		return (NULL);
	ft_lstadd_back(word_list, node);
	if (!node->content)
		return (NULL);
	return (str + i);
}

/// @brief Parse the next word unit encountered and adds it to word_list
/// @param str
/// @param word_list
/// @param quote
/// @param env
/// @return Pointer toward the character following the word found or
/// ```NULL``` if allocation error.
char	*t_word_parse_next(char *str, t_list **word_list, bool *quote,
			t_data *data)
{
	if (!*quote && *str == '\'')
		str = get_simple_quote(++str, *quote, word_list);
	else if (str && *str == '"')
	{
		*quote = !*quote;
		return (++str);
	}
	else if (str && *str == '$' && ft_isalnum(*(str + 1)))
		str = get_var_string(++str, *quote, word_list, data);
	else if (str && *str == '$' && *(str + 1) == '?')
		str = t_word_get_exit_status(++str, *quote, word_list, data);
	else if (str && *str == '*' && !*quote)
		str = get_wc_string(str, *quote, word_list);
	else
		str = get_word_string(str, word_list, *quote);
	return (str);
}
