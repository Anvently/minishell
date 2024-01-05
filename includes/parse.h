/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:41:46 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/04 13:23:09 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef enum 	e_atom_type
{
	redirection_in,
	redirection_out,
	separator,
	simple_quote,
	double_quote,
	space,
	variable,
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
	end_of_line,
	none,
}		t_atom_subtype;


typedef struct s_atom
{
	char			*content;
	t_atom_type		type;
	t_atom_subtype	subtype;
}			t_atom;



#endif
