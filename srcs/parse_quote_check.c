/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:35:10 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/11 16:31:57 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

int	check_between(char *str, char a, char b)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (str[i] && str[i] != a)
	{
		if (str[i] == b)
			count++;
		i++;
	}
	if (count % 2 > 0)
		return (-1);
	if (str[i] == 0)
		return (-1);
	return (i);
}
/// @brief check if there is no quote errors
/// @param str the chain to check
/// @return -1 on error, positive value elsewise

int	quote_check(char *str)
{
	int	i;
	int	res;

	i = 0;
	while (str[i])
	{
		res = 0;
		if (str[i] == 34)
			res = check_between(str + i, 34, 39);
		if (str[i] == 39)
			res = check_between(str + i, 39, 34);
		if (res < 0)
			break ;
		i += res + 1;
	}
	return (res);
}

void	quote_litteral(t_atom *pt)
{
	t_atom_type		quote_type;

	while (pt && pt->type != QUOTE && pt->type != D_QUOTE)
		pt = pt->next;
	if (pt)
	{
		quote_type = pt->type;
		pt = pt->next;
	}
	while (pt && pt->type != quote_type)
	{
		if (pt->type == variable && quote_type == D_QUOTE)
		{
			pt = pt->next;
			continue ;
		}
		pt->type = litteral;
		pt ->subtype = none;
		pt = pt->next;
	}
	if (pt)
		quote_litteral(pt->next);
}

void	trim_quotes(t_atom *atom)
{
	if (!atom)
		return ;
	while (atom)
	{
		if (atom->type == QUOTE || atom->type == D_QUOTE)
		{
			atom->type = litteral;
			atom->subtype = none;
		}
		atom = atom->next;
	}
}
