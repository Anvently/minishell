/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 09:57:30 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/09 16:51:02 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <parse.h>

/*
the 3 funcions below will replace the $VAR by the actual value of the variable
if the variable doesnt exists the dollar becomes a space to be trimmed later
*/
// int	get_variable_name(t_atom *atom, char **env)
// {
// 	char	*str;
// 	t_atom	*pt;

// 	str = NULL;
// 	pt = atom;
// 	if (!atom)
// 		return (0);
// 	while (atom && atom->type != variable)
// 		atom = atom->next;
// 	if (!atom)
// 		return (0);
// 	while(atom->next && atom->next->type == litteral)
// 	{
// 		if (merge_atom(&atom, &atom->next, variable, none))
// 		{
// 			free_atom_list(pt);
// 			ft_free_strs(env);
// 			parse_error(-1, NULL);
// 		}
// 	}
// 	if (atom->next)
// 		get_variable_name(atom->next, env);
// 	return (0);
// }

// int	replace_dollar_value(t_atom *pt, char **env)
// {
// 	char	*temp;

// 	if (pt->content[1])
// 	{
// 		temp = get_var_value((pt->content + 1), env);
// 		if (!temp)
// 		{
// 			ft_free_strs(env);
// 			return (-1);
// 		}
// 		free(pt->content);
// 		pt->content = temp;
// 		pt->type = litteral;
// 	}
// 	else
// 	{
// 		pt->content[0] = ' ';
// 		pt->type = space;
// 	}
// 	return (0);
// }

// int	expand_dollar(t_atom *atom, char **env)
// {
// 	t_atom	*pt;

// 	pt = atom;
// 	get_variable_name(pt, env);
// 	while (pt)
// 	{
// 		if (pt->type == variable)
// 		{
// 			if (replace_dollar_value(pt, env))
// 			{
// 				free_atom(atom);
// 				parse_error(-1, NULL);
// 				exit (-1);
// 			}
// 		}
// 		pt = pt->next;
// 	}
// 	return (0);
// }

/*
the two function below merge sequence of concomitant litterals
*/

// int	merge_variable(t_atom *atom)
// {
// 	t_atom	*pt;
// }

int	create_word(t_atom *pt, char **env)
{
	while (pt && pt->next && pt->next->type == litteral)
	{
		if (merge_atom(&pt, &pt->next, litteral, none))
		{
			ft_free_strs(env);
			return (-1);
		}
	}
	return (0);
}

int	merge_litteral(t_atom *atom, char **env)
{
	t_atom	*pt;

	pt = atom;
	while (pt)
	{
		if (pt->type == litteral)
		{
			if (create_word(pt, env))
			{
				free_atom_list(atom);
				parse_error(-1, NULL);
				exit (-1);
			}
		}
		pt = pt->next;
	}
	return (0);
}
