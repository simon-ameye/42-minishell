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
					tokenisation.c \
					dollar_expand.c \
					dollar_expand_utils.c \
					print_tokens.c \
					free_tokens.c \
					get_words.c \
					get_ftype.c \
					get_path.c \
					minishell_utils.c \
					builtin_exit.c \
					builtin_pwd.c \
					builtin_env.c

SOURCES		=		$(addprefix $(SRCS_DIR)/,$(SRCS))

#################	OBJECT FILES	#################

OBJS		=		$(addsuffix .o, $(basename $(SRCS)))

OBJECTS		=		$(addprefix $(OBJS_DIR)/,$(OBJS))

################	BINARIES		#################

NAME		=		minishell

################	LIBFT			#################

LIBFT		=		$(LIBFT_DIR)/libft.a
LINK		=		-L $(LIBFT_DIR) -l ft

################	TESTS			#################

#RELINK!
test_tokenisation:	$(LIBFT)
					@$(CC) $(TESTS_DIR)/main_tokenisation.c \
					src/tokenisation.c src/get_words.c src/dollar_expand_utils.c \
					$(INCLUDE) $(LINK) -o main_tokenisation
					@valgrind ./main_tokenisation

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

test_exit:			$(LIBFT)
					@$(CC) $(TESTS_DIR)/main_exit.c \
					src/builtin_exit.c src/tokenisation.c \
					src/free_tokens.c src/get_words.c \
					src/minishell_utils.c \
					src/dollar_expand_utils.c\
					$(INCLUDE) $(LINK) -o main_exit
					@valgrind ./main_exit

################	TARGETS			#################

debug:
					$(info $(SRCS))
					$(info $(OBJS))
					$(info $(SOURCES))
					$(info $(OBJECTS))

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

.PHONY:				all clean fclean re debug test_tokenisation test_expand test_get_words
