/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_atom_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:54:37 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/05 11:51:33 by lmahe            ###   ########.fr       */
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


