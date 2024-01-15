/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:35:10 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/15 15:35:40 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

int	quote_error(char c)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	write(2, "`", 1);
	write(2, &c, 1);
	write(1, "'\n", 2);
	return (2);
}


int	quote_check(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (!line || *line == 0)
		return (0);
	while (line[i] && line[i] != '\"' && line[i] != '\'')
		i++;
	if (line[i])
	{
		while (line[i + j] && line[i + j] != line[i])
			j++;
		if (!line[i + j] || line[i + j] != line[i])
			return (quote_error(line[i]));
		else
		{
			i += j + 1;
			if (line[i])
				return (quote_check (line + i));
		}
	}
	return (0);
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

