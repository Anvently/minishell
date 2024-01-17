/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:48:28 by npirard           #+#    #+#             */
/*   Updated: 2024/01/17 17:03:31 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>

# include <fcntl.h>
# include <errno.h>

# define HEREPATH "/tmp/heredoc_"
# define COLOR_YELLOW "\001\033[1;33m\002"
# define COLOR_RESET   "\001\033[1;0m\002"

/// @note interperet : 0 = NO || 1 = YES
/// @note append_mod : 0 = NO || 1 = YES
/// @note type       : 0 = <  || 1 = << || 2 = > || 3 = >>
typedef struct s_file_rd {
	char	*path;
	int		type;
	bool	unlink;
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
	t_list		*files;
	t_list		*argv;
}				t_command;

typedef struct s_data {
	t_list		*pipe_list;
	char		**env;
	int			exit_status;
	char		*exe_path;
	char		*prompt;
	int			stdout_copy;
	int			stdin_copy;
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

int			error(int err, char *str);
int			parse_error(int err, char *str);
int			builtin_error(int err, char *builtin, char *value, char *context);
int			free_data(int err, t_data *data);

/* ---------------------------------- UTILS --------------------------------- */

bool		is_abs_path(char *str);
bool		is_directory(char *path);
char		*path_join(char const *path, char const *tail);

/* -------------------------------------------------------------------------- */
/*                                   PARSING                                  */
/* -------------------------------------------------------------------------- */

int			parse_line(t_list **lst, char *line);

/* -------------------------------------------------------------------------- */
/*                              PIPES & COMMANDS                              */
/* -------------------------------------------------------------------------- */

/* -------------------------------- EXECUTION ------------------------------- */

int			exec_pipe(t_list *commands, t_data *data, int *old_fd);
int			exec_prompt(t_list *pipe_list, t_data *data);
int			exec_command(char **argv, int *fd, int *old_fd, t_data *data);
int			exec_builtin(char **argv, t_data *data);

/* ---------------------------------- UTILS --------------------------------- */

int			clear_pipe(int err, int fd);
int			dup_and_close(int file_fd, int std_fd);
int			file_redirect(char *path, int fd_out, int o_flag);
int			command_find_path(char *command, char **path_dest, char **env);
int			restore_std(t_data *data);

/* ------------------------------ COMMAND CHECK ----------------------------- */

bool		command_is_builtin(char *command);

/* -------------------------------- META-CHARACTERS ------------------------- */

int			interpret_metachar(char *str, t_list **results, t_data *data);
int			check_file_meta(t_file_rd *file, t_data *data);
int			interpret_argv(t_list *argv, t_data *data);
int			t_word_parse(char *str, t_list **word_list, t_data *data);
char		*t_word_parse_next(char *str, t_list **word_list, bool *quote,
				t_data *data);
char		*t_word_get_exit_status(char *str, t_list **word_list,
				t_data *data);
int			t_word_concat_dup(t_list *word_list);
int			t_word_interpret(t_list *words, t_list **results);
bool		t_word_match(t_list *word_list, char *path);

/* --------------------------- STRUCT T_WORD UTILS -------------------------- */

t_list		*t_word_new_node(char *str, char type);
void		t_word_init(t_word *word, char *str, char type);
void		t_word_free(void *word);
void		t_word_print(void *content);
char		*t_word_concat_str(t_list *word_list);

/* -------------------------------------------------------------------------- */
/*                                  BUILTINs                                  */
/* -------------------------------------------------------------------------- */

void		builtin_exit(char **argv, t_data *data);
int			builtin_echo(char **argv);
int			builtin_env(char **env);
int			builtin_export(char **argv, char ***env);
int			builtin_unset(char **argv, char ***env);
int			builtin_pwd(void);
int			builtin_cd(char **argv, char ***env);
int			cd_find_path(char **buf, char *path, char **env);

/* -------------------------------------------------------------------------- */
/*                                     ENV                                    */
/* -------------------------------------------------------------------------- */

char		**env_copy(char **env, int size);
int			set_var_value(char *var, char *value, char ***env);
char		*get_var_value(char *var, char **env);
bool		is_var_defined(char *var, char **env);

/* -------------------------------------------------------------------------- */
/*                                    STRUCTS UTILS                           */
/* -------------------------------------------------------------------------- */

t_list		*new_file_node(void);
t_list		*new_pipe_node(void);
t_list		*new_cmd_node(void);
void		free_t_command(void *comd);
void		free_t_file(void *file);
void		free_t_pipe(void *tpip);
t_command	*init_t_command(t_command *cmd);
t_pipe		*init_t_pipe(t_pipe *pip);
void		init_t_file(t_file_rd *file);
void		lst_display(t_list *pt, void (*disp)(void *));
void		file_display(void *file);
void		command_display(void *command);
void		pipe_display(void *pip);

/* -------------------------------------------------------------------------- */
/*                                    INIT MAIN                               */
/* -------------------------------------------------------------------------- */

t_data		*init_data(void);
char		*make_prompt(t_data *data);
char		*colorize_prompt(char *prompt);
char		*replace_with_tilde(char *path, t_data *data);

/* -------------------------------------------------------------------------- */
/*                                   SIGNALS                                  */
/* -------------------------------------------------------------------------- */

int			rec_signal(void);
int			rec_heredoc_signal(void);

#endif
