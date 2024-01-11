/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 09:57:30 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/11 16:33:01 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

int	create_word(t_atom *pt)
{
	while (pt && pt->next && pt->next->type == litteral)
	{
		if (merge_atom(&pt, &pt->next, litteral, none))
			return (-1);
	}
	return (0);
}

int	merge_litteral(t_atom *atom)
{
	t_atom	*pt;

	pt = atom;
	while (pt)
	{
		if (pt->type == litteral)
		{
			if (create_word(pt))
				return (-1);
		}
		pt = pt->next;
	}
	return (0);
}
