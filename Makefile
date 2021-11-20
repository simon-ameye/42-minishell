################	COMPILER		#################

CC			=		gcc -Wall -Wextra -Werror

################	DIRECTORIES		#################

OBJS_DIR	=		obj/

LIBFT_DIR	=		libft/

#################	HEADER FILES	#################

INCLUDE		=		-I libft/

#################	SOURCE FILES	#################

SRCS		=		minishell.c \
					tokenisation.c \
					dollar_expand.c \
					dollar_expand_utils.c

#################	OBJECT FILES	#################

OBJS		=		$(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

################	BINARIES		#################

NAME		=		minishell

################	LIBFT			#################

LIBFT		=		$(LIBFT_DIR)libft.a
LINK		=		-L $(LIBFT_DIR) -l ft

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
