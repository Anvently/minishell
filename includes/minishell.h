/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:48:28 by npirard           #+#    #+#             */
/*   Updated: 2024/01/05 12:01:02 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>

/// @note interperet : 0 = NO || 1 = YES
/// @note append_mod : 0 = NO || 1 = YES
typedef struct s_file_rd {
	char	*path;
	bool	interpret_wc;
	bool	interpret_var;
	bool	append_mode;
}			t_file_rd;

/// @brief A pipe is defined as a list of ```t_command``` separated by ```|```.
/// @param commands List of ```t_command``` structures
/// @param condition  0 = Always execute, 1 = &&, 2 = ||
typedef struct s_pipe {
	t_list		*commands;
	int			condition;
}				t_pipe;

/// @brief A command is defined as such [(< file_in)*n][ cmd][(> file_out)*n]
/// @param files_in List of ```t_file_rd``` structure :
/// "file1, /usr/customfile, /tmp/here_doc1, ..., ```NULL```"
/// @note If no file_in given, files_in is ```NULL```
/// @param files_out List of ```t_file_rd``` struct.
/// @note If no file_out given, files_out is ```NULL```
/// @param argv argv[0] = cmd path, or cmd name if builtin, followed by args.
/// Ends with ```NULL```.
/// @note If no command given, argv is ```NULL```
typedef struct s_command {
	t_list		*files_in;
	t_list		*files_out;
	char		**argv;
}				t_command;

/* ---------------------------------- ERROR --------------------------------- */

int		error(int err, char *str);
int 	parse_error(int err, char *str);

/* -------------------------------------------------------------------------- */
/*                              PIPES & COMMANDS                              */
/* -------------------------------------------------------------------------- */

/* -------------------------------- EXECUTION ------------------------------- */

int		exec_pipe(t_list *commands, char **env, int *old_fd);
int		exec_prompt(t_list *pipe_list, char **env);
int		exec_command(t_command *command, int *fd, int *old_fd, char **env);
int		exec_builtin(t_command *command, char **env);

/* ---------------------------------- UTILS --------------------------------- */

void	clear_pipe(int fd);
int		dup_and_close(int file_fd, int std_fd);
int		file_redirect(char *path, int fd_out, int o_flag);
char	*command_find_path(char *command, char **env);

/* ------------------------------ COMMAND CHECK ----------------------------- */

bool	command_is_builtin(char *command);
bool	command_is_path(char *command);

/* -------------------------------- META-CHARACTERS ------------------------- */

char	*get_var_value(char *var, char **env);
int		expand_wc(char *path, char *dest);
int		check_file_meta(t_list *files, char **env);

#endif
