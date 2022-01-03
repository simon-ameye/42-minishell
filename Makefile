################	COMPILER		#################

CC			=		gcc -Wall -Wextra -Werror

################	DIRECTORIES		#################

SRCS_DIR	=		src

OBJS_DIR	=		obj

LIBFT_DIR	=		libft

TESTS_DIR	=		testmains

INCLUDE_DIR	=		include

#################	HEADER FILES	#################

INCLUDE		=		-I include \
					-I libft \
					-I /opt/homebrew/opt/readline/include/

#################	SOURCE FILES	#################

SRCS		=		minishell.c \
					get_procs.c \
					get_procs_1.c \
					free_procs.c \
					get_tokens.c \
					get_tokens_1.c \
					get_tokens_2.c \
					string.c \
					get_token_type.c \
					get_token_type_1.c \
					get_path.c \
					get_path_1.c \
					get_fnct_type.c \
					get_fds.c \
					exec.c \
					exec_child.c \
					builtin_env.c \
					builtin_echo.c \
					builtin_echo_1.c \
					builtin_exit.c \
					builtin_pwd.c \
					builtin_cd.c \
					builtin_unset.c \
					builtin_export.c \
					builtin_export_1.c \
					builtin_utils.c \
					env.c \
					here_doc.c \
					here_doc_1.c \
					signals.c \
					run_execve.c\
					fd_tools.c\
					remove_quotes_and_expand.c\
					remove_quotes_and_expand_1.c\
					remove_quotes_and_expand_2.c

SOURCES		=		$(addprefix $(SRCS_DIR)/,$(SRCS))

#################	OBJECT FILES	#################

OBJS		=		$(addsuffix .o, $(basename $(SRCS)))
OBJECTS		=		$(addprefix $(OBJS_DIR)/,$(OBJS))

################	BINARIES		#################

NAME		=		minishell

################	LIBFT			#################

LIBFT		=		$(LIBFT_DIR)/libft.a
LINK		=		-L $(LIBFT_DIR) -l ft -L /opt/homebrew/opt/readline/lib

################	TARGETS			#################

all:				$(NAME)

$(OBJS_DIR):
					mkdir -p $@

$(OBJECTS):			$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
					@$(CC) $(INCLUDE) -c $< -o $@

$(NAME):			$(OBJS_DIR) $(LIBFT) $(OBJECTS)
					@echo Building minishell...
					@$(CC) $(INCLUDE) $(OBJECTS) -o $(NAME) $(LINK) -lreadline

$(LIBFT):
					@echo Building libft...
					@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

clean:
					@echo Cleaning minishell objects...
					@$(MAKE) clean --no-print-directory -C $(LIBFT_DIR)
					@rm -f $(OBJECTS)

fclean:				clean
					@echo Cleaning minishell binary...
					@$(MAKE) fclean --no-print-directory -C $(LIBFT_DIR)
					@rm -f $(NAME)

re:					fclean all

.PHONY:				all clean fclean re
