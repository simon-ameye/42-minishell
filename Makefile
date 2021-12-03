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
					-I libft

#################	SOURCE FILES	#################

SRCS		=		minishell.c \
					get_procs.c \
					print_procs.c \
					free_procs.c \
					get_tokens.c \
					string.c \
					dollar_expand.c \
					get_token_type.c \
					get_path.c \
					get_fnct_type.c \
					remove_quotes.c \
					get_fds.c \
					exec.c \
					exec_child.c \
					builtin_env.c \
					builtin_echo.c \
					builtin_exit.c \
					builtin_pwd.c \
					builtin_cd.c \
					builtin_unset.c \
					builtin_export.c \
					env.c \
					here_doc.c \
					set_ignored_tokens.c

SOURCES		=		$(addprefix $(SRCS_DIR)/,$(SRCS))

#################	OBJECT FILES	#################

OBJS		=		$(addsuffix .o, $(basename $(SRCS)))

OBJECTS		=		$(addprefix $(OBJS_DIR)/,$(OBJS))

################	BINARIES		#################

NAME		=		minishell

################	LIBFT			#################

LIBFT		=		$(LIBFT_DIR)/libft.a
LINK		=		-L $(LIBFT_DIR) -l ft

all:				$(NAME)

$(OBJS_DIR):
					@mkdir -p $@

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c $(OBJS_DIR)
					@$(CC) $(INCLUDE) -c $< -o $@

$(NAME):			$(LIBFT) $(OBJECTS)
					@echo Building minishell...
					@$(CC) $(INCLUDE) $(OBJECTS) -o $(NAME) $(LINK) -lreadline

$(LIBFT):
					@echo Building libft...
					@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

clean:
					@echo Cleaning minishell objects...
					@rm -f $(OBJECTS)

fclean:				clean
					@echo Cleaning minishell binary...
					@$(MAKE) fclean --no-print-directory -C $(LIBFT_DIR)
					@rm -f $(NAME)

re:					fclean all

.PHONY:				all clean fclean re debug test_get_procs test_expand test_get_words

################	TESTS			#################

#RELINK!
test_get_procs:		$(LIBFT)
					@$(CC) $(TESTS_DIR)/main_get_procs.c \
					src/get_procs.c src/get_words.c src/dollar_expand_utils.c \
					$(INCLUDE) $(LINK) -o main_get_procs
					@valgrind ./main_get_procs

#UNUSABLE!			UNABLE TO ADD ENV VAR
test_expand:		$(LIBFT)
					@$(CC) $(TESTS_DIR)/main_dollar_expand.c \
					src/dollar_expand.c src/dollar_expand_utils.c \
					$(INCLUDE) $(LINK) -o main_dollar_expand
					@echo Please do 'export TESTVAR=/cust/path'
#					$(shell export TESTVAR=/cust/path) # HERE
					@valgrind ./main_dollar_expand

#RELINK!
test_get_words:		$(LIBFT)
					@$(CC) $(TESTS_DIR)/main_get_words.c \
					src/get_words.c src/dollar_expand_utils.c \
					$(INCLUDE) $(LINK) -o main_get_words
					@valgrind ./main_get_words


################	TARGETS			#################

debug:
					$(info $(SRCS))
					$(info $(OBJS))
					$(info $(SOURCES))
					$(info $(OBJECTS))