NAME = minishell
INC = minishell.h

SRCS = minishell.c lexer.c

OBJS_DIR = obj
OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))
CC = gcc -Wall -Wextra -Werror

LFT_DIR = ./libft/
LFT_LIB = $(LFT_DIR)libft.a
LFT_LNK = -L $(LFT_DIR) -l ft

all : $(OBJS_DIR) $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(NAME) : $(LFT_LIB) $(OBJS)
	$(CC) $(OBJS) $(LFT_LNK) -o $@ -lreadline

$(OBJS_DIR)/%.o : %.c
	@echo "compiling $<"
	@$(CC) -I $(LFT_DIR) -c $< -o $@

$(LFT_LIB):
	$(MAKE) -C $(LFT_DIR)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
