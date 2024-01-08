/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:21:33 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/08 08:55:27 by lmahe            ###   ########.fr       */
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
				return (1);
			pt = pt->next;
		}
		else if (pt)
			pt = pt->next;
	}
	return (0);
}

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
				return (1);
			pt = pt->next;
		}
		else if (pt)
			pt = pt->next;
	}
	return (0);
}
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
				return (1);
			pt = pt->next;
		}
		else if (pt)
			pt = pt->next;
	}
	return (0);
}
// int	check_void_redir(t_atom *atom, int *index)
// {
// 	int		space_check;
// 	t_atom	*pt;

// 	space_check = 0;
// 	pt = atom;
// 	while (pt && pt->type != separator && pt->type != redirection_in && pt->type != redirection_out)
// 	{
// 		if (pt->type == litteral)
// 			space_check = 1;
// 		pt = pt->next;
// 	}
// 	if ((space_check == 0) && (pt && pt->next))
// 		return (parse_error(1, pt->content));
// 	else if ((space_check == 0) || (pt && !pt->next))
// 		return (parse_error(1, "\'newline\'"));
// 	else if (pt && pt->next)
// 		return (check_void(pt->next));
// 	else
// 		return (0);
// }
// t_atom	*check_void_redir(t_atom *atom)
// {
// 	int		space_check;
// 	t_atom	*pt;

// 	space_check = 0;
// 	while (pt && pt->type != redirection_in && pt->redirection_out)
// 		pt = pt->next;
// 	if (pt && !pt->next)
// 		return (pt);
// 	pt = pt->next;
// 	while (pt && pt->type != redirection_in && pt->type!= redirection_out && pt->type != separator)
// 	{
// 		if (pt->type == litteral ||pt->type == wildcard)
// 			space_check = 1;
// 		pt = pt->next;
// 	}
// 	if (space_check == 0)
// 	{
// 		if(pt)
// 			return (pt);
// 		else if (!pt)
// 			return (atom_last(atom));
// 	}
// 	else if (space_check == 0 && pt)
// 		return (check_void_redir(pt));
// 	else
// 		return (NULL);
// }
