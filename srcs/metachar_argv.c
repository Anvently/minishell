/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:11:12 by npirard           #+#    #+#             */
/*   Updated: 2024/01/12 10:55:09 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

static t_list	*merge_results(t_list *argv, t_list **results);
static int		expand_arg(t_list *arg, t_list **next, t_data *data);
static int		check_parenthesis(t_list *argv, t_data *data);
int				interpret_argv(t_list *argv, t_data *data);

/// @brief Insert results list in place of argv node. Current argv content
/// is replaced with the content of the first result.
/// @param argv
/// @param results Size is always >= 1.
/// @param next Address of a pointer toward the next element in the list,
/// which is equal to the node following current argv node before merging.
/// @return Pointer toward old argv->next
static t_list	*merge_results(t_list *argv, t_list **results)
{
	t_list	*next_result;

	free(argv->content);
	argv->content = (*results)->content;
	next_result = (*results)->next;
	free(*results);
	*results = next_result;
	return (ft_lstmerge(argv, results));
}

/// @brief Check if given arg contain metacharacter to interpret and if
/// insert every match in the list after arg.
/// @param argv A string list's node
/// @param data
/// @return ```0``` for success. ```errno``` if error.
static int	expand_arg(t_list *arg, t_list **next, t_data *data)
{
	t_list	*results;
	t_list	*word_list;
	char	*arg_str;
	int		err;

	err = 0;
	arg_str = (char *)arg->content;
	if (t_word_parse(arg_str, &word_list, data))
		return (error(errno, "parsing word"));
	if (t_word_concat_dup(word_list))
	{
		ft_lstclear(&word_list, t_word_free);
		return (error(errno, "concatenating word"));
	}
	results = NULL;
	err = t_word_interpret(word_list, &results);
	if (!err)
		*next = merge_results(arg, &results);
	ft_lstclear(&results, free);
	ft_lstclear(&word_list, t_word_free);
	return (err);
}

/// @brief Check if current node start with parenthesis and if so
/// remove them and insert a node before which is the path to minishell
/// executable.
/// @param argv
/// @param data
/// @return ```0``` for success (no parenthesis found is a success).
/// ```errno``` if error (allocation error).
static int	check_parenthesis(t_list *argv, t_data *data)
{
	char	*new_str;
	char	*path_exe;

	path_exe = ft_strdup(data->exe_path);
	if (!path_exe)
		return (errno);
	new_str = ft_strtrim((char *)argv->content, "()");
	if (!new_str)
	{
		free(path_exe);
		return (errno);
	}
	if (ft_lst_str_append(&argv, new_str))
	{
		free(path_exe);
		free(new_str);
		return (errno);
	}
	free(new_str);
	free(argv->content);
	argv->content = path_exe;
	return (0);
}

/// @brief Check metacharacters for every node of argv list and insert
/// all matches in the list.
/// @param argv first element of argv (which is the name of the command)
/// is not checked.
/// @param data
/// @return ```0``` for success. ```errno``` if error
int	interpret_argv(t_list *argv, t_data *data)
{
	if (argv && ((char *)argv->content)[0] == '(')
	{
		if (check_parenthesis(argv, data))
			return (error(errno, "interpreting parenthesis"));
		return (0);
	}
	while (argv)
	{
		if (argv && expand_arg(argv, &argv, data))
			return (errno);
	}
	return (0);
}
