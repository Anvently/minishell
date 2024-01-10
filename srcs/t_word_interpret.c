/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_word_interpret.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:49:42 by npirard           #+#    #+#             */
/*   Updated: 2024/01/10 18:58:20 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <errno.h>
#include <unistd.h>
#include <linux/limits.h>

static int	append_result(t_list **results, char *str);
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

/// @brief Search for match of t_word units in working directory.
/// @param words Succession of t_word unit of different types (either litterals
/// or ```*```).
/// @param results List of string to store the resulting matches.
/// @return ```0```if no error occured.
/// ```errno``` if error occured.
int	t_word_interpret(t_list *words, t_list **results)
{
	char	wk_dir_path[PATH_MAX];

	if (!words->next && ((t_word *)words->content)->type != '*')
		if (append_result(results, ((t_word *)words->content)->content))
			return (errno);
	if (!getcwd(wk_dir_path, PATH_MAX))
		return (errno);
	return (0);
}
