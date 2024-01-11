/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:38:51 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/11 14:39:47 by lmahe            ###   ########.fr       */
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
		atom =atom->next;
	}
}
int	check_double_errors(t_atom *atom, char **env)
{
 	int	check;

	check = check_double_redir(atom, redirection_in, double_in);
	if (check)
		return (parse_free(atom, env, check, NULL));
 	check = check_double_redir(atom, redirection_out, double_out);
	if (check)
		return (parse_free(atom, env, check, NULL));
	check = check_double_pipe(atom);
	if (check)
		return (parse_free(atom, env, check, NULL));
	check = check_double_and(atom);
	if (check < 0)
		return (parse_free(atom, env, check, NULL));
	return (check);
}

int	main(int argc, char **argv, char **env)
{
	t_atom *pt;
	char	*line = "<file1 <<LIM cat -e | (grep 458 >out) && echo 4 || <<LIM grep 4 | sleep 4 >>out";
	t_list	*lst;

	(void)argv;
	(void)argc;
	lst = NULL;
	pt = parse_by_atom(line);
	quote_litteral(pt);
	trim_quotes(pt);
	//expand_dollar(pt, env);
	merge_litteral(pt, env);
	merge_space(pt, env);
	//print_atom(pt);
	if (check_double_errors(pt, env) == 0)
	{
		syntax_check(pt);
		litteralize_parenthesis(pt);
		printf("@@@@@@@@@@@@@@@@@@@@@\n");
		print_atom(pt);
		printf("@@@@@@@@@@@@@@@@@@@@@\n");
	}
	build_struct(&lst, &pt, 0);
	lst_display(lst, pipe_display);
	//print_atom(pt);
	free_atom_list(pt);
}
