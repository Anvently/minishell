/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parenthesis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:35:23 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/19 11:32:10 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

t_atom	*parenthesis_order(t_atom *atom)
{
	int		count;
	t_atom	*pt;

	count = 0;
	pt = atom;
	while (pt)
	{
		if (pt->subtype == right_p && !count)
			break ;
		if (pt->subtype == right_p && count)
			count--;
		if (pt->subtype == left_p)
			count++;
		pt = pt->next;
	}
	return (pt);
}

t_atom	*parenth_close(t_atom *atom)
{
	int		count;
	t_atom	*pt;

	pt = atom;
	count = 0;
	while (pt)
	{
		if (pt->subtype == right_p && !count)
			break ;
		if (pt->subtype == right_p && count)
			count--;
		if (pt->subtype == left_p)
			count++;
		pt = pt->next;
	}
	if (count)
		return (go_to(atom, "(", parenth, left_p));
	else
		return (NULL);
}

t_atom	*parenthesis_left_neighbor(t_atom *atom)
{
	t_atom	*pt;
	t_atom	*previous;
	t_atom	*next;

	pt = atom;
	while (1)
	{
		pt = go_to(pt, NULL, parenth, left_p);
		if (!pt)
			break ;
		previous = go_to_previous(atom, pt);
		next = skip_space(pt->next);
		if (previous && previous->type == litteral)
			return (pt);
		if (next && next->type == separator)
			return (next);
		pt = pt->next;
	}
	return (NULL);
}

t_atom	*parenthesis_right_neighbor(t_atom *atom)
{
	t_atom	*pt;
	t_atom	*next;
	t_atom	*error;

	error = NULL;
	pt = atom;
	while (1)
	{
		pt = go_to(pt, NULL, parenth, right_p);
		if (!pt)
			break ;
		else
		{
			next = skip_space(pt->next);
			if (next && next->type == litteral)
			{
				error = next;
				break ;
			}
		}
		pt = pt->next;
	}
	return (error);
}

t_atom	*parenthesis_syntax(t_atom *atom)
{
	t_atom	*error;
	t_atom	*pt;

	error = parenthesis_order(atom);
	pt = parenthesis_left_neighbor(atom);
	error = find_first(error, pt, atom);
	pt = parenthesis_right_neighbor(atom);
	error = find_first(error, pt, atom);
	pt = void_parenthesis(atom);
	error = find_first(error, pt, atom);
	return (error);
}
