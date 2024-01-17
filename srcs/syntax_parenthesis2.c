/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parenthesis2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:14:43 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/17 15:17:59 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

static int	only_space(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

t_atom	*void_parenthesis(t_atom *atom)
{
	t_atom	*error;
	t_atom	*pt;

	error = NULL;
	pt = atom;
	while (1)
	{
		pt = go_to(pt, NULL, parenth, left_p);
		if (!pt)
			break ;
		else
		{
			if (pt->next->subtype == right_p)
				return (pt->next);
			if (only_space(pt->next->content))
				return (pt->next->next);
		}
		pt = pt->next;
	}
	return (error);
}
