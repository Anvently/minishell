/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:38:51 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/15 17:38:27 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

int	only_space(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == 32 || \
		(str[i] >= 9 && str[i] <= 13))
			i++;
		else
			return (0);
	}
	return (1);
}

int	atomize_line(char *line, t_atom **atom)
{
	*atom = parse_by_atom(line);
	if (!*atom)
		return (-1);
	quote_litteral(*atom);
	trim_quotes(*atom);
	if (merge_litteral(*atom) < 0)
		return (-1);
	if (merge_space(*atom) < 0)
		return (-1);
	return (check_double_errors(*atom));
}

int	parse_line(t_list **lst, char *line)
{
	t_atom	*atom;
	int		error;

	if (!line)
		return (0);
	if (only_space(line))
		return (0);
	if (quote_check(line))
		return (2);
	error = atomize_line(line, &atom);
	if (error)
		return (parse_free(atom, error));
	error = syntax_check(atom);
	if (error)
		return (parse_free(atom, error));
	if (litteralize_parenthesis(atom) < 0)
		return (parse_free(atom, -1));
	if (build_struct(lst, &atom, 0) < 0)
		return (parse_free(atom, -1));
	free_atom_list(atom);
	return (0);
}


