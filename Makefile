NAME = minishell
INC = minishell.h

SRCS = minishell.c lexer.c

OBJS_DIR = obj
OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))
CC = gcc -Wall -Wextra -Werror

LIBFT_DIR = ./libft/
LIBFT_LIB = $(LIBFT_DIR)libft.a
LIBFT_LNK = -L $(LIBFT_DIR) -l ft

all : $(OBJS_DIR) $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(NAME) : $(LIBFT_LIB) $(OBJS)
	$(CC) $(OBJS) $(LIBFT_LNK) -o $@ -lreadline

$(OBJS_DIR)/%.o : %.c
	@echo "compiling $<"
	@$(CC) -I $(LIBFT_DIR) -c $< -o $@

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)
#$(MAKE) --no-print-directory -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJS)

fclean: clean
#$(MAKE) fclean --no-print-directory -C $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
