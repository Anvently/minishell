/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:21:33 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/10 13:15:26 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

/// @brief check for >> and << merge them and assign the good subtype
/// @param atom the first atom of the list
/// @param type the type > or < to check for
/// @param subt the subtype to assign
/// @return
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
/// @brief check for || and assign its subtype
/// @param atom the list to check
/// @return
int	check_double_pipe(t_atom *atom)
{
	t_atom	*pt;

	pt = atom;
	while (pt)
	{
		while (pt && pt->subtype != pipeline)
			pt = pt->next;
		if (pt && (pt->next && pt->next->subtype == pipeline))
		{
			if (merge_atom(&pt, &pt->next, separator, x_or) < 0)
				return (-1);
			pt = pt->next;
		}
		else if (pt)
			pt = pt->next;
	}
	return (0);
}
/// @brief checks for && and merge and assign the correct subtype
/// @param atom
/// @return
int	check_double_and(t_atom *atom)
{
	t_atom	*pt;

	pt = atom;
	while (pt)
	{
		while (pt && pt->subtype != s_and)
			pt = pt->next;
		if (pt && (pt->next && pt->next->subtype != s_and))
		{
			parse_error(1, "\'&\'");
			return (1);
		}
		else if (pt && pt->next && pt->next->subtype == s_and)
		{
			if (merge_atom(&pt, &pt->next, separator, double_and) < 0)
				return (-1);
			pt = pt->next;
		}
		else if (pt)
			pt = pt->next;
	}
	return (0);
}

