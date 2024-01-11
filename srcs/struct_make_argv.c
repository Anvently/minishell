/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_make_argv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:00:30 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/11 14:22:46 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parse.h>
#include <libft.h>

t_list	*get_argv(t_atom **atom, t_atom *next)
{
	t_atom	*pt;
	t_list	*new;

	new = NULL;
	pt = skip_space(*atom);
	if (pt->type == parenth)
	{
		if (merge_atom(&pt, &pt->next, litteral, none) < 0)
			return (NULL);
		if (merge_atom(&pt, &pt->next, litteral, none) < 0)
			return (NULL);
	}
	while (pt && pt != next)
	{
		if (pt->type == litteral)
		{
			if (ft_lst_str_append(&new, pt->content) < 0)
				return (NULL);
		}
		pt = pt->next;
	}
	return (new);
}

