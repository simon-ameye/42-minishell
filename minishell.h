#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

#include "libft.h"

typedef enum e_function_type
{
	EXECVE,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_function_type;

typedef struct	s_token
{
	char			*str;
	char			*path;
	char			**args;
	char			**words;
	char *const		*env;
	t_function_type	ftype;
	int				input;
	int				output;
//	bool			is_child; // `cd /` vs `cd / | cd /`
//	pid_t			pid;
	int				is_last;
}	t_token;

#include "tokenisation.h"
#include "dollar_expand.h"
#include "get_words.h"

# endif
