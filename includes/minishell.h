/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:48:28 by npirard           #+#    #+#             */
/*   Updated: 2024/01/03 16:37:13 by npirard          ###   ########.fr       */
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

/// @brief A pipe is defined as a list of ```t_command``` separated by ```|```.
/// @param condition  0 = Always execute, 1 = &&, 2 = ||
typedef struct s_pipe {
	t_list		*commands;
	int			condition;
}				t_pipe;

/// @brief A command is defined as such [(< file_in)*n][ cmd][(> file_out)*n]
/// @param files_in "file1, /usr/customfile, /tmp/here_doc1, ..., ```NULL```"
/// @note If no file_in given, files_in is ```NULL```
/// @param files_out Ends with ```NULL```.
/// @note If no file_out given, files_out is ```NULL```
/// @param argv argv[0] = cmd path, or cmd name if builtin, followed by args.
/// Ends with ```NULL```.
/// @note If no command given, argv is ```NULL```
typedef struct s_command {
	char		**files_in;
	t_outfile	*files_out;
	char		**argv;
}				t_command;

/* ---------------------------------- ERROR --------------------------------- */

int	error(int err, char *str);

/* -------------------------------- EXECUTION ------------------------------- */

int	exec_pipe(t_pipe *pipe, char **env, int *old_fd, int i_command);
int	exec_prompt(t_list *pipe_list, char **env);

#endif
