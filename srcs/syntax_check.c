/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:23:17 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/11 16:36:23 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

t_atom	*find_first(t_atom *a1, t_atom *a2, t_atom *list)
{
	if (!a1 && !a2)
		return (NULL);
	while (list != a1 && list != a2)
		list = list->next;
	return (list);
}

t_atom	*first_error(t_atom *pt, t_atom *start)
{
	static t_atom	*error = NULL;

	if (start && pt)
	{
		if (error == NULL)
			error = pt;
		else if (pt->type != end_of_line)
			error = find_first(error, pt, start);
	}
	return (error);
}

int	empty_line(t_atom *atom)
{
	while (atom && atom->type == space)
		atom = atom->next;
	if (!atom)
		return (1);
	return (0);
}

int	syntax_check(t_atom *atom)
{
	t_atom	*error;
	t_atom	*newline;

	if (empty_line(atom))
		return (1);
	newline = create_atom("newline", end_of_line, none);
	if (!newline)
		return (-1);
	error = parenthesis_syntax(atom);
	error = first_error(error, atom);
	error = redir_syntax(atom, newline);
	error = first_error(error, atom);
	error = separator_syntax(atom, newline);
	error = first_error(error, atom);
	if (error)
	{
		parse_error(1, error->content);
		free_atom(newline);
		return (1);
	}
	free_atom(newline);
	error = parenth_close(atom);
	if (error)
		return (parse_error(1, error->content));
	return (0);
}
