/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_atom_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:54:37 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/11 10:10:44 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

void	free_atom_list(t_atom *pt)
{
	t_atom	*temp;

	if (!pt)
		return ;
	while (pt)
	{
		temp = pt;
		pt = pt->next;
		if (temp->content)
			free(temp->content);
		free(temp);
	}
}
void	delete_atom(t_atom *previous, t_atom *to_del)
{
	t_atom	*pt;

	if (!previous || !to_del)
		return ;
	pt = to_del->next;
	previous->next = pt;
	free_atom(to_del);
}

t_atom	*atom_last_but_one(t_atom *atom)
{
	t_atom	*pt;

	if (!atom || !atom->next)
		return (NULL);
	pt = atom->next;
	while (pt != NULL)
	{
		atom = atom->next;
		pt = pt->next;
	}
	return (atom);
}

t_atom	*remove_file_from_atom(t_atom *atom, t_atom *file)
{
	t_atom	*previous;

	if (atom == file)
	{
		atom = atom->next->next;
		previous = file->next;
		free_atom(file);
		while (previous->type != litteral)
		{
			file = previous;
			previous = previous->next;
			free_atom(file);
		}
		free_atom(previous);
		return (atom);
	}
	previous = atom;
	while (previous->next != file)
		previous = previous->next;
	delete_atom(previous, file);
	delete_atom(previous, previous->next);
	return (atom);
}
