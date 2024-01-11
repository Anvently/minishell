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
				struct_make_argv.c


OBJS		=	$(addprefix $(OBJS_FOLDER),$(SRCS_FILES:.c=.o))
SRCS		=	$(addprefix $(SRCS_FOLDER),$(SRCS_FILES))

LIBFT		=	libft/libft.a

DEPS		=	$(LIBFT) $(INCLUDES)$(NAME).h $(INCLUDES)libft.h Makefile

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

re: fclean all
