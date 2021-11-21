################	COMPILER		#################

CC			=		gcc -Wall -Wextra -Werror

################	DIRECTORIES		#################

OBJS_DIR	=		obj/

LIBFT_DIR	=		libft/

TESTS_DIR	=		testmains/

#################	HEADER FILES	#################

INCLUDE		=		-I . \
					-I libft/

#################	SOURCE FILES	#################

SRCS		=		minishell.c \
					tokenisation.c \
					dollar_expand.c \
					dollar_expand_utils.c \
					get_words.c

#################	OBJECT FILES	#################

OBJS		=		$(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

################	BINARIES		#################

NAME		=		minishell

################	LIBFT			#################

LIBFT		=		$(LIBFT_DIR)libft.a
LINK		=		-L $(LIBFT_DIR) -l ft

################	TESTS			#################

#RELINK!
test_tokenisation:	$(LIBFT)
					@$(CC) $(TESTS_DIR)main_tokenisation.c \
					tokenisation.c get_words.c dollar_expand_utils.c \
					$(INCLUDE) $(LINK) -o main_tokenisation
					@valgrind ./main_tokenisation

#UNUSABLE!			UNABLE TO ADD ENV VAR
test_expand:		$(LIBFT)
					@$(CC) $(TESTS_DIR)main_dollar_expand.c \
					dollar_expand.c dollar_expand_utils.c \
					$(INCLUDE) $(LINK) -o main_dollar_expand
					$(shell export TESTVAR=/cust/path) # HERE
					@valgrind ./main_dollar_expand

#RELINK!
test_get_words:		$(LIBFT)
					@$(CC) $(TESTS_DIR)main_get_words.c \
					get_words.c dollar_expand_utils.c \
					$(INCLUDE) $(LINK) -o main_get_words
					@valgrind ./main_get_words

################	TARGETS			#################

all:				$(OBJS_DIR) $(NAME)

$(OBJS_DIR):
					mkdir -p $(OBJS_DIR)

$(NAME):			$(LIBFT) $(OBJS)
					#echo Building minishell...
					$(CC) $(INCLUDE) $(OBJS) -o $(NAME) $(LINK) -lreadline

$(OBJS_DIR)/%.o:	%.c
					#@echo "compiling $<"
					$(CC) -c $< -o $@ $(INCLUDE) $(LINK)

$(LIBFT):
					#echo Building libft...
					$(MAKE) --no-print-directory -C $(LIBFT_DIR)

clean:
					#echo Cleaning objects...
					rm -rf $(OBJS)

fclean:				clean
					#echo Cleaning binaries...
					$(MAKE) fclean --no-print-directory -C $(LIBFT_DIR)
					rm -rf $(NAME)

re:					fclean all


.PHONY:				all clean fclean re
