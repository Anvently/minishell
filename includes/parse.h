/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:41:46 by lmahe             #+#    #+#             */
/*   Updated: 2024/01/11 14:58:27 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define QUOTE 3
# define D_QUOTE 4


typedef enum	e_atom_type
{
	redirection_in,
	redirection_out,
	separator,
	simple_quote,
	double_quote,
	space,
	variable,
	wildcard,
	litteral,
	parenth,
	end_of_line
}			t_atom_type;

typedef enum	e_atom_subtype
{
	pipeline,
	double_and,
	x_or,
	simple_in,
	double_in,
	simple_out,
	double_out,
	s_and,
	left_p,
	right_p,
	var,
	none,
}		t_atom_subtype;


typedef struct s_atom
{
	char			*content;
	t_atom_type		type;
	t_atom_subtype	subtype;
	struct s_atom	*next;
}			t_atom;



int		quote_check(char *str);

/*-----------------ATOMS--------------------*/
void	free_atom(t_atom *atom);
void	free_atom_list(t_atom *pt);
t_atom	*create_atom(char *str, int type, int subtype);
int		merge_atom(t_atom **a1, t_atom **a2,
			t_atom_type type, t_atom_subtype subtype);
t_atom	*atom_last(t_atom *pt);
void	atom_addback(t_atom **pt, t_atom *atom);
t_atom	*parse_by_atom(char *line);
void	trim_quotes(t_atom *pt);
void	print_atom(t_atom *atom);
void	delete_atom(t_atom *previous, t_atom *to_del);
t_atom	*atom_last_but_one(t_atom *atom);
t_atom	*skip_space(t_atom *atom);
t_atom	*go_to(t_atom *atom, char *content,
			t_atom_type type, t_atom_subtype subt);
t_atom	*go_to_previous(t_atom *list, t_atom *target);
t_atom	*remove_file_from_atom(t_atom *atom, t_atom *file);

/*---------------ATOMS CHECK------------------*/
int		check_double_redir(t_atom *atom, t_atom_type type, t_atom_subtype subt);
int		check_double_pipe(t_atom *atom);
int		check_double_and(t_atom *atom);
int		check_void(t_atom *atom);
int		expand_dollar(t_atom *atom, char **env);
int		merge_litteral(t_atom *atom, char **env);
int		merge_space(t_atom *atom, char **env);
int		parse_free(t_atom *atom, char **env, int err, char *str);
t_atom	*find_first(t_atom *a1, t_atom *a2, t_atom *list);

/*---------------SYNTAX CHECK--------------------------*/

int		syntax_check(t_atom *atom);
t_atom	*parenthesis_syntax(t_atom *atom);
t_atom	*redir_syntax(t_atom *atom, t_atom *newline);
t_atom	*separator_syntax(t_atom *atom, t_atom *newline);
t_atom	*parenth_close(t_atom *atom);

/*-----------------BUILD STRUCT--------------------*/

int		litteralize_parenthesis(t_atom *atom);
t_list	*get_commands(t_list **lst, t_atom **atom, t_atom *end);
t_list	*get_files(t_atom **start, t_atom *end);
t_list	*get_argv(t_atom **atom, t_atom *next);
int		build_struct(t_list **lst, t_atom **atom, int condition);




#endif
