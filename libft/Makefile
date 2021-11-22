OBJS_DIR		=	obj/
INCS_DIR		= 	include/
INC 			= 	libft.h
NAME 			= 	libft.a

SRCS			= 	ft_atoi.c \
					ft_isascii.c \
					ft_memccpy.c \
					ft_memset.c  \
					ft_putstr_fd.c \
					ft_strjoin.c \
					ft_strncmp.c \
					ft_substr.c \
					ft_bzero.c \
					ft_isblank.c \
					ft_memchr.c  \
					ft_split.c \
					ft_strlcat.c \
					ft_strncpy.c \
					ft_tolower.c \
					ft_calloc.c  \
					ft_isdigit.c \
					ft_memcmp.c  \
					ft_putchar_fd.c  \
					ft_strchr.c  \
					ft_strlcpy.c \
					ft_strnstr.c \
					ft_toupper.c \
					ft_isalnum.c \
					ft_isprint.c \
					ft_memcpy.c  \
					ft_putendl_fd.c  \
					ft_strcpy.c  \
					ft_strlen.c  \
					ft_strrchr.c \
					ft_isalpha.c \
					ft_itoa.c \
					ft_memmove.c \
					ft_putnbr_fd.c \
					ft_strdup.c  \
					ft_strmapi.c \
					ft_strtrim.c \
					ft_strcmp.c

BONUS_SRC		 = 	ft_lstnew.c \
					ft_lstadd_front.c \
					ft_lstsize.c \
					ft_lstlast.c \
					ft_lstadd_back.c \
					ft_lstdelone.c \
					ft_lstclear.c \
					ft_lstiter.c \
					ft_lstmap.c

OBJS			=	$(SRCS:.c=.o)
BONUS_OBJS		=	$(BONUS_SRCS:.c=.o)

DIROBJS			=	$(addprefix $(OBJS_DIR),$(OBJS))
BONUS_DIROBJS	=	$(addprefix $(OBJS_DIR),$(BONUS_OBJS))

CC				=	gcc -Wall -Wextra -Werror

all:				$(NAME)

$(NAME):			$(OBJS_DIR) $(DIROBJS)
					@echo Building mandatory libft...
					@ar rcs $(NAME) $(DIROBJS)

$(DIROBJS):			$(OBJS_DIR)%.o: %.c
					@$(CC) -c $< -o $@

$(BONUS_DIROBJS):	$(OBJS_DIR)%.o: %.c
					@$(CC) -c $< -o $@

$(OBJS_DIR):
					@mkdir $@

clean:
					@echo Cleaning libft objects...
					@rm -rf $(DIROBJS) $(BONUS_DIROBJS)

fclean:				clean
					@echo Cleaning libft library...
					@rm -rf $(NAME)

re:					fclean all

bonus:				$(DIROBJS) $(BONUS_DIROBJS)
					@echo Building bonus libft...
					@ar rcs $(NAME) $(DIROBJS) $(BONUS_DIROBJS) $(NAME)

.PHONY:				all clean fclean re bonus
