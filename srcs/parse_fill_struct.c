/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:41:32 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/09 16:44:08 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

t_atom	*skip_space(t_atom *atom)
{
	if (!atom)
		return (NULL);
	while (atom && atom->type == space)
		atom = atom->next;
	return (atom);
}


