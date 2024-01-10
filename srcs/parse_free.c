/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:00:25 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/10 08:43:50 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

int	parse_free(t_atom *atom, char **env, int err, char *str)
{
	free_atom_list(atom);
	if (err == -1)
		ft_free_strs(env);
	parse_error(err, str);
	if (err == -1)
		exit (-1);
	return (err);
}

t_atom	*go_to(t_atom *atom, char *content, t_atom_type type, t_atom_subtype subt)
{
	if (content)
	{
		while (atom && atom->content[0] != content[0])
			atom =atom->next;
		return (atom);
	}
	else if (subt <= 42)
	{
		while (atom && (atom->type != type || atom->subtype != subt))
			atom =atom->next;
		return (atom);
	}
	else
	{
		while(atom && atom->type != type)
			atom= atom->next;
		return (atom);
	}
}

t_atom	*go_to_previous(t_atom *list, t_atom *target)
{
	t_atom	*pt;

	pt = list;
	if (target == list)
		return (NULL);
	while (pt && pt->next != target)
		pt = pt->next;
	if (pt->type == space)
		pt = go_to_previous(list, pt);
	return (pt);
}

t_atom	*skip_space(t_atom *atom)
{
	if (!atom)
		return (NULL);
	while (atom && atom->type == space)
		atom = atom->next;
	return (atom);
}
