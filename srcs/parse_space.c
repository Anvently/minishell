/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:42:41 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/08 14:48:04 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

/*
the 2 functins below will merge sequence of spaces into just one
*/
int	create_space(t_atom *pt, char **env)
{
	while (pt && pt->next && pt->next->type == space)
	{
		if (merge_atom(&pt, &pt->next, space, none))
		{
			ft_free_strs(env);
			return (-1);
		}
	}
	return (0);
}

int	merge_space(t_atom *atom, char **env)
{
	t_atom	*pt;

	pt = atom;
	while (pt)
	{
		if (pt->type == space)
		{
			if (create_space(pt, env))
			{
				free_atom_list(atom);
				parse_error(-1, NULL);
				exit (-1);
			}
		}
		pt = pt->next;
	}
	return (0);

}


