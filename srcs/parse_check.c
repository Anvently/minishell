/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:21:33 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/05 14:45:14 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

int	check_double_redir(t_atom *atom, t_atom_type type, t_atom_subtype subt)
{
	t_atom	*pt;

	pt = atom;
	while (pt)
	{
		while (pt && pt->type != type)
			pt = pt->next;
		if (pt && (pt->next && pt->next->type == type))
		{
			if (merge_atom(&pt, &pt->next, type, subt) < 0)
				return (-1);
			pt = pt->next;
		}
		else if (pt)
			pt = pt->next;
	}
	return (0);
}

int	check_double_sep(t_atom *atom, t_atom_subtype oldsub, t_atom_subtype newsub)
{
	t_atom	*pt;

	pt = atom;
	while (pt)
	{
		while (pt && pt->subtype != oldsub)
			pt = pt->next;
		if (if pt && oldsub == s_and)
		{
			if (!pt->next || pt->next != oldsub)
		}
	}
}
