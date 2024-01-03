/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:48:28 by npirard           #+#    #+#             */
/*   Updated: 2024/01/03 15:01:54 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>

/// @brief append_mod : 0 = TRUNC || 1 = APPEND
typedef struct s_outfile {
	char	*path;
	bool	append_mode;
}			t_outfile;

/// @brief
/// @param files_in "file1, /usr/customfile, /tmp/here_doc1, etc...."
/// @param condition  0 = Always execute, 1 = &&, 2 = ||
typedef struct s_pipe {
	char		**files_in; //
	t_outfile	*files_out;
	char		***commands;
	int			condition;
}				t_pipe;

/* ---------------------------------- ERROR --------------------------------- */

int	error(int err, char *str);

#endif
