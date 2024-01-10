/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_atom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:32:36 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/10 08:52:32 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

/*
the two function below are used to get the type of a given character
it allocates memory inside an atom node to store the character
*/
t_atom	*find_type(t_atom *new, char c, t_atom types[])
{
	int		i;
	char	str[2];

	i = 0;
	str[0] = c;
	str[1] = 0;
	new->content = ft_strdup(str);
	if (!(new->content))
	{
		free(new);
		return (NULL);
	}
	new->type = litteral;
	new->subtype = none;
	while (types[i].content)
	{
		if (ft_strcmp(str, types[i].content) == 0)
		{
			new->type = types[i].type;
			new->subtype = types[i].subtype;
		}
		i++;
	}
	return (new);
}

t_atom	*get_type(t_atom *new, char c)
{
	static t_atom	types[] = {
	{"<", redirection_in, simple_in, NULL},
	{"<<", redirection_in, double_in, NULL},
	{">", redirection_out, simple_out, NULL},
	{">>", redirection_out, double_out, NULL},
	{"|", separator, pipeline, NULL},
	{"&&", separator, double_and, NULL},
	{"&", separator, s_and, NULL},
	{"||", separator, x_or, NULL},
	{"'", simple_quote, none, NULL},
	{"\"", double_quote, none, NULL},
	{"$", litteral, var, NULL},
	{"*", wildcard, none, NULL},
	{" ", space, none, NULL},
	{"\t", space, none, NULL},
	{"\r", space, none, NULL},
	{"\f", space, none, NULL},
	{"(", parenth, left_p, NULL},
	{")", parenth, right_p, NULL},
	{0, 0, 0, 0}
	};

	new = find_type(new, c, types);
	return (new);
}

void	print_atom(t_atom *atom)
{
	if (!atom)
		return ;
	while (atom)
	{
		ft_printf("content: %s, type: %d, subtype: %d\n", \
		atom->content, atom->type, atom->subtype);
		atom = atom->next;
	}
}
/// @brief parse the line and assign its type to each character
/// @param line
/// @return a pointer to the first atom of the line
t_atom	*parse_by_atom(char *line)
{
	t_atom	*pt;
	t_atom	*atom;

	pt = NULL;
	while (*line)
	{
		atom = create_atom(NULL, litteral, none);
		if (!atom)
		{
			free_atom_list(pt);
			return (NULL);
		}
		atom = get_type(atom, *line);
		if (!atom)
		{
			free_atom_list(pt);
			return (NULL);
		}
		atom_addback(&pt, atom);
		line++;
	}
	return(pt);
}


