/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 09:35:45 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/11 16:33:58 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <parse.h>

t_atom	*find_closing(t_atom *atom)
{
	int		count;
	t_atom	*pt;

	pt = atom->next;
	count = 0;
	while (pt)
	{
		if (pt && pt->subtype == right_p && count == 0)
			break ;
		if (pt && pt->subtype == right_p && count)
			count--;
		if (pt && pt->subtype == left_p)
			count++;
		pt = pt->next;
	}
	return (pt);
}

int	litteralize_atoms(t_atom *start, t_atom *end)
{
	t_atom	*pt;

	pt = start->next;
	if (pt == end)
		return (0);
	while (pt->next != end)
	{
		if (merge_atom(&pt, &pt->next, litteral, none) < 0)
			return (-1);
	}
	return (0);
}

int	litteralize_parenthesis(t_atom *atom)
{
	t_atom	*closing_p;

	atom = go_to(atom, NULL, parenth, left_p);
	if (!atom)
		return (0);
	closing_p = find_closing(atom);
	if (litteralize_atoms(atom, closing_p) < 0)
		return (-1);
	atom = closing_p;
	return (litteralize_parenthesis(atom));
}
