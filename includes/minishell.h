/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:48:28 by npirard           #+#    #+#             */
/*   Updated: 2024/01/11 14:29:13 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>

# include <fcntl.h>
# include <errno.h>

# define HEREPATH "/tmp/heredoc_"

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
	char		***env;
}				t_data;

///* #### Word are separated by :
///*		- ['" $*] (space),
///*		- when inside '', nothing is separated
///* ```content``` Litteral content of word
///* #### quote
///* ```quote = 0``` outside quote (* and $ are interpreted)
///* ```quote = "``` "" (only $ are interpreted)
///* ```quote = '``` '' (no metachar are interpreted)
///* #### type
///* ```type = 0``` litteral
///* ```type = $``` variable (not including $)
///* ```type = *``` wildcard (not including *, content is NULL)
typedef struct s_word {
	char		*content;
	char		quote;
	char		type;

}				t_word;

/* --------------------------- STRUCT T_WORD UTILS -------------------------- */

t_list	*t_word_new_node(void);
void	t_word_init(t_word *word);
void	t_word_free(void *word);

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


int		expand_var(char *str, t_list **results, char **env);
int		check_files_meta(t_list *files, char **env);

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
void	init_t_file(t_file_rd *file);
void	lst_display(t_list *pt, void (*disp)(void *));
void	file_display(void *file);
void	command_display(void *command);
void	pipe_display(void *pip);

#endif
