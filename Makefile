NAME		=	minishell
BONUS_NAME	=

INCLUDES	=	includes/
SRCS_FOLDER	=	srcs/
OBJS_FOLDER	=	objs/

SRCS_FILES	=	parse_atom.c \
				parse.c \
				parse_atom_utils.c \
				parse_atom_utils2.c \
				parse_check.c \
				parse_free.c \
				parse_quote_check.c \
				parse_space.c \
				parse_variable.c \
				parse_parenthesis.c \
				struct_utils1.c \
				struct_utils2.c \
				struct_make_files.c \
				syntax_check.c \
				syntax_parenthesis.c \
				syntax_redirection.c \
				syntax_separator.c \
				error.c \
				struct_display.c \
				struct_make.c \
				struct_make_argv.c \
				builtin_cd.c builtin_cd2.c builtin_echo.c builtin_env.c \
				builtin_exit.c builtin_export.c builtin_pwd.c builtin_unset.c \
				command_check.c command_exec.c command_path.c \
				env.c env2.c \
				metachar_argv.c metachar_files.c metachar.c \
				pipe.c execution.c \
				t_word_interpret.c t_word_parsing.c t_word_parsing2.c \
				t_word_util.c \
				utils_files.c utils.c \
				minishell.c \
				data.c \
				make_prompt.c \
				make_prompt2.c\
				struct_make_heredoc.c \
				signal_handler.c


OBJS		=	$(addprefix $(OBJS_FOLDER),$(SRCS_FILES:.c=.o))
SRCS		=	$(addprefix $(SRCS_FOLDER),$(SRCS_FILES))

LIBFT		=	libft/libft.a

DEPS		=	$(LIBFT) $(INCLUDES)$(NAME).h $(INCLUDES)libft.h \
				$(INCLUDES)parse.h Makefile

STATIC_LINK	=	-Llibft/ -lft -lreadline

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3 -I$(INCLUDES)

.PHONY		=	all clean fclean test re bonus

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "\n-----COMPILING $(NAME)-------\n"
	$(CC) $(CFLAGS) $(OBJS) $(STATIC_LINK) -o $(NAME)
	@echo "Executable has been successfully created."

bonus: $(BONUS_NAME)

$(OBJS_FOLDER)%.o: $(SRCS_FOLDER)%.c $(DEPS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(INCLUDES)libft.h: libft/libft.h
	@echo "------ UPDATING LIBFT HEADER -------\n"
	cp libft/libft.h includes/libft.h

$(LIBFT): $(INCLUDES)libft.h
	@echo "\n-------COMPILING LIBFT--------------\n"
	make -C libft/
	make clean -C libft/
	@echo "\n\n"

clean:
	@echo "\n-------------CLEAN--------------\n"
	make clean -C libft/
	rm -rf $(OBJS_FOLDER)
	@echo "object files have been removed."

fclean: clean
	@echo "\n-------------FORCE CLEAN--------------\n"
	make fclean -C libft/
	rm -rf $(NAME) $(BONUS_NAME)
	@echo "$(NAME) and object files have been removed."

vallog:
	valgrind -s --leak-check=full --show-reachable=yes --show-leak-kinds=all \
	--error-limit=no --suppressions=./minishell.supp --gen-suppressions=all \
	--log-file=minishell.log --trace-children=yes --track-fds=yes ./minishell

re: fclean all
