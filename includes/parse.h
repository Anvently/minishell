/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:41:46 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/05 17:32:52 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define QUOTE 3
# define D_QUOTE 4


typedef enum 	e_atom_type
{
	redirection_in,
	redirection_out,
	separator,
	simple_quote,
	double_quote,
	space,
	variable,
	wildcard,
	litteral
}			t_atom_type;

typedef enum	e_atom_subtype
{
	simple_in,
	double_in,
	simple_out,
	double_out,
	pipeline,
	double_and,
	x_or,
	s_and,
	none,
}		t_atom_subtype;


typedef struct s_atom
{
	char			*content;
	t_atom_type		type;
	t_atom_subtype	subtype;
	struct s_atom	*next;
}			t_atom;



int	quote_check(char *str);

/*-----------------ATOMS--------------------*/
void	free_atom(t_atom *atom);
void	free_atom_list(t_atom *pt);
t_atom	*create_atom(char *str, int type, int subtype);
int		merge_atom(t_atom **a1, t_atom **a2, t_atom_type type, t_atom_subtype subtype);
t_atom	*atom_last(t_atom *pt);
void	atom_addback(t_atom **pt, t_atom *atom);
t_atom	*parse_by_atom(char *line);
void	trim_quotes(t_atom **pt);
void	print_atom(t_atom *atom);

/*---------------ATOMS CHECK------------------*/
int	check_double_redir(t_atom *atom, t_atom_type type, t_atom_subtype subt);
int	check_double_pipe(t_atom *atom);
int	check_double_and(t_atom *atom);
int	check_void(t_atom *atom);





#endif
