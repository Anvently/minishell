/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_atom_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:06:33 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/11 16:23:14 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

/// @brief create a atom node and return a pointer to it
/// @param str the content of the node
/// @param type the type
/// @param subtype
/// @return
t_atom	*create_atom(char *str, int type, int subtype)
{
	t_atom	*new;

	new = malloc(sizeof(t_atom));
	new->type = type;
	new->subtype = subtype;
	new->content = NULL;
	new->next = NULL;
	if (str)
	{
		new->content = ft_strdup(str);
		if (!new->content)
		{
			free(new);
			new = NULL;
		}
	}
	return (new);
}

void	free_atom(t_atom *atom)
{
	if (!atom)
		return ;
	if (atom->content)
		free(atom->content);
	atom->next = NULL;
	free(atom);
}
/// @brief merge two atom into the first
/// @param a1 the first atom
/// @param a2 the second one, to be free'ed during the process
/// @param type the type of the new atom
/// @param subtype ..
/// @return

int	merge_atom(t_atom **a1, t_atom **a2, \
t_atom_type type, t_atom_subtype subtype)
{
	char	*temp;
	t_atom	*pt;

	temp = ft_strjoin((*a1)->content, (*a2)->content);
	pt = (*a2)->next;
	if (temp == NULL)
		return (-1);
	free_atom(*a2);
	(*a1)->next = pt;
	free((*a1)->content);
	(*a1)->content = temp;
	(*a1)->type = type;
	(*a1)->subtype = subtype;
	return (0);
}

t_atom	*atom_last(t_atom *pt)
{
	if (!pt)
		return (NULL);
	while (pt && pt->next)
		pt = pt->next;
	return (pt);
}

void	atom_addback(t_atom **pt, t_atom *atom)
{
	if (!pt)
		return ;
	else if (!*pt)
		*pt = atom;
	else
		atom_last(*pt)->next = atom;
}
