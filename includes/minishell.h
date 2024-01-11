/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:48:28 by npirard           #+#    #+#             */
/*   Updated: 2024/01/11 13:19:41 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>

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

typedef struct s_data {
	t_list		*pipe_list;
	char		**env;
	int			exit_status;
	char		*exe_path;
}				t_data;

///* #### Word are separated by :
///*		- ['" $*] (space),
///*		- when inside '', nothing is separated
///* ```content``` Litteral content of word
///* #### quote
///* ```quote = false``` outside quote (* and $ are interpreted)
///* ```quote = true``` "" (only $ are interpreted)
///* #### type
///* ```type = 0``` litteral
///* ```type = $``` variable (not including $)
///* ```type = *``` wildcard (not including *, content is NULL)
typedef struct s_word {
	char		*content;
	char		type;
}				t_word;

/* ---------------------------------- ERROR --------------------------------- */

int		error(int err, char *str);
int		parse_error(int err, char *str);
int		builtin_error(int err, char *builtin, char *value, char *context);
int		free_data(int err, t_data *data);

/* ---------------------------------- UTILS --------------------------------- */

bool	is_abs_path(char *str);
bool	is_directory(char *path);
char	*path_join(char const *path, char const *tail);

/* -------------------------------------------------------------------------- */
/*                              PIPES & COMMANDS                              */
/* -------------------------------------------------------------------------- */

/* -------------------------------- EXECUTION ------------------------------- */

int		exec_pipe(t_list *commands, t_data *data, int *old_fd);
int		exec_prompt(t_list *pipe_list, t_data *data);
int		exec_command(t_command *command, int *fd, int *old_fd, t_data *data);
int		exec_builtin(t_command *command, t_data *data);

/* ---------------------------------- UTILS --------------------------------- */

void	clear_pipe(int fd);
int		dup_and_close(int file_fd, int std_fd);
int		file_redirect(char *path, int fd_out, int o_flag);
char	*command_find_path(char *command, char **env);

/* ------------------------------ COMMAND CHECK ----------------------------- */

bool	command_is_builtin(char *command);

/* -------------------------------- META-CHARACTERS ------------------------- */

int		interpret_metachar(char *str, t_list **results, t_data *data);
int		check_files_meta(t_list *files, t_data *data);
int		t_word_parse(char *str, t_list **word_list, t_data *data);
char	*t_word_parse_next(char *str, t_list **word_list, bool *quote,
			t_data *data);
char	*t_word_get_exit_status(char *str, t_list **word_list, t_data *data);
int		t_word_concat_dup(t_list *word_list);
int		t_word_interpret(t_list *words, t_list **results);

/* --------------------------- STRUCT T_WORD UTILS -------------------------- */

t_list	*t_word_new_node(char *str, char type);
void	t_word_init(t_word *word, char *str, char type);
void	t_word_free(void *word);
void	t_word_print(void *content);
char	*t_word_concat_str(t_list *word_list);

/* -------------------------------------------------------------------------- */
/*                                  BUILTINs                                  */
/* -------------------------------------------------------------------------- */

void	builtin_exit(char **argv);
int		builtin_echo(char **argv);
int		builtin_env(char **env);
int		builtin_export(char **argv, char ***env);
int		builtin_unset(char **argv, char ***env);
int		builtin_pwd(void);
int		builtin_cd(char **argv, char ***env);
int		cd_find_path(char **buf, char *path, char **env);

/* -------------------------------------------------------------------------- */
/*                                     ENV                                    */
/* -------------------------------------------------------------------------- */

char	**env_copy(char **env, int size);
int		set_var_value(char *var, char *value, char ***env);
char	*get_var_value(char *var, char **env);
bool	is_var_defined(char *var, char **env);

#endif
