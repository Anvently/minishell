/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:41:32 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/19 11:33:23 by npirard          ###   ########.fr       */
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
