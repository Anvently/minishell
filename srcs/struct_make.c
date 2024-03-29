/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_make.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:12:24 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/02 11:27:16 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>
#include <errno.h>

t_atom	*find_logical_separator(t_atom *atom)
{
	if (!atom)
		return (NULL);
	while (atom && atom->subtype != x_or && atom->subtype != double_and)
		atom = atom->next;
	return (atom);
}

t_atom	*find_next_pipe(t_atom *start, t_atom *end)
{
	while (start && start != end && start->subtype != pipeline)
		start = start->next;
	return (start);
}

t_list	*get_commands(t_list **lst, t_atom **atom, t_atom *end)
{
	t_list		*new;
	t_atom		*next_pipe;

	new = new_cmd_node();
	if (!new)
		return (NULL);
	ft_lstadd_back(lst, new);
	next_pipe = find_next_pipe(*atom, end);
	((t_command *)new->content)->files = get_files(atom, next_pipe);
	if (!((t_command *)new->content)->files
		&& (errno == ENOMEM || errno == 130))
		return (ft_lstclear(lst, free_t_command), NULL);
	((t_command *)new->content)->argv = get_argv(atom, next_pipe);
	if (!((t_command *)new->content)->argv && errno == ENOMEM)
		return (ft_lstclear(lst, free_t_command), NULL);
	if (next_pipe == end)
		return (*lst);
	return (get_commands(lst, &next_pipe->next, end));
}

int	build_struct(t_list **lst, t_atom **atom, int condition)
{
	t_atom	*next_separator;
	t_list	*new;

	if (!*atom)
		return (0);
	new = new_pipe_node();
	if (!new)
		return (-1);
	next_separator = find_logical_separator(*atom);
	((t_pipe *)new->content)->commands = \
	get_commands(&((t_pipe *)new->content)->commands, atom, next_separator);
	if (!new->content || errno == 130)
	{
		ft_lstdelone(new, free_t_pipe);
		return (-1);
	}
	((t_pipe *)new->content)->condition = condition;
	ft_lstadd_back(lst, new);
	if (!next_separator)
		return (0);
	return (build_struct(lst, &next_separator->next, next_separator->subtype));
}
