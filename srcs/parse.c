/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:38:51 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/08 08:55:58 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

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
void	trim_quotes(t_atom **atom)
{
	t_atom	*pt;

	if (!atom || !*atom)
		return ;
	pt = *atom;
	if((*atom)->type == QUOTE || (*atom)->type == D_QUOTE)
	{
		*atom = (*atom)->next;
		free_atom(pt);
		trim_quotes(atom);
	}
	else
	{
		trim_quotes(&pt->next);
	}
}
int	check_double_errors(t_atom *atom)
{
 	if (check_double_redir(atom, redirection_in, double_in) > 0)
		return (1);
 	if (check_double_redir(atom, redirection_out, double_out) > 0)
		return (1);
	if (check_double_pipe(atom) > 0)
		return (1);
	if (check_double_and(atom) > 0)
		return (1);
	//if (check_void(atom) > 0)
	//	return (1);
	return (0);
}


// int	trim_atoms(t_atom **atom)
// {
// 	quote_litteral(*atom);
// 	trim_quotes(atom);
	//*atom = expand_dollar(*atom);



// }

// t_list	*parse_line(char *line, char **env)
// {
// 	t_atom	*atom_line;

// 	atom_line = NULL;
// 	if (quote_check(line) < 0)
// 	{
// 		parse_error("quote error");
// 		return (NULL);
// 	}
// 	atom_line = parse_by_atom(line); //create a node by character and assign its type
// 	if (!atom_line)
// 		return (NULL);
// 	if (trim_atoms(&atom_line) < 0)
// 		return (NULL);
// 	parsed_line = merge_atom(parse_line); // put together atom of size type and checks egs |||
// 	if (!parsed_line)
// 		return (NULL);
// 	parsed_line = get_pipe_list(parse_line); // create the t_pipe elements
// 	return (parsed_line);
// }


int	main(void)
{
	t_atom *pt;
	char	*line = "   dfd |    >>  d   ";

	pt = parse_by_atom(line);
	quote_litteral(pt);
	trim_quotes(&pt);
	if (check_double_errors(pt) == 0)
	{
		printf("@@@@@@@@@@@@@@@@@@@@@\n");
		print_atom(pt);
	}
}
