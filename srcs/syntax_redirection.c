/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:45:48 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/11 16:36:59 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

t_atom	*redir_in(t_atom *atom, t_atom *newline)
{
	t_atom	*error;
	t_atom	*pt;
	t_atom	*next;

	error = NULL;
	pt = atom;
	while (pt)
	{
		if (pt->type == redirection_in)
		{
			next = skip_space(pt->next);
			if (!next)
			{
				error = newline;
				break ;
			}
			if (next->type != litteral)
			{
				error = next;
				break ;
			}
		}
		pt = pt->next;
	}
	return (error);
}

t_atom	*redir_out(t_atom *atom, t_atom *newline)
{
	t_atom	*error;
	t_atom	*pt;
	t_atom	*next;

	error = NULL;
	pt = atom;
	while (pt)
	{
		if (pt->type == redirection_out)
		{
			next = skip_space(pt->next);
			if (!next)
			{
				error = newline;
				break ;
			}
			if (next->type != litteral)
			{
				error = next;
				break ;
			}
		}
		pt = pt->next;
	}
	return (error);
}

t_atom	*redir_syntax(t_atom *atom, t_atom *newline)
{
	t_atom	*error;
	t_atom	*pt;

	error = redir_in(atom, newline);
	pt = redir_out(atom, newline);
	if (!error && pt)
		error = pt;
	else if (error == newline && pt)
		error = pt;
	else if (error && pt == newline)
		pt = error;
	else
		error = find_first(error, pt, atom);
	return (error);
}
