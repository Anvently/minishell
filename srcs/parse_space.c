/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:42:41 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/11 16:32:23 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

/*
the 2 functins below will merge sequence of spaces into just one
*/
int	create_space(t_atom *pt)
{
	while (pt && pt->next && pt->next->type == space)
	{
		if (merge_atom(&pt, &pt->next, space, none))
		{
			return (-1);
		}
	}
	return (0);
}

int	merge_space(t_atom *atom)
{
	t_atom	*pt;

	pt = atom;
	while (pt)
	{
		if (pt->type == space)
		{
			if (create_space(pt))
			{
				return (-1);
			}
		}
		pt = pt->next;
	}
	return (0);
}
