/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_separator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:37:59 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/11 16:37:38 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

t_atom	*separator_syntax(t_atom *atom, t_atom *newline)
{
	t_atom	*pt;
	t_atom	*next;
	t_atom	*error;

	pt = skip_space(atom);
	if (pt->type == separator)
		return (pt);
	error = NULL;
	while (1)
	{
		pt = go_to(pt->next, NULL, separator, 42);
		if (!pt)
			break ;
		next = skip_space(pt->next);
		if (next && (next->type == separator))
		{
			error = next;
			break ;
		}
		if (!next)
			return (newline);
	}
	return (error);
}
