#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef enum e_ftype
{
	EXECVE,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_ftype;

typedef struct	s_token
{
	char			*str;
	char			*path;
	char			**args;
	char			**words;
	t_ftype			ftype;
	int				fdin;
	int				fdout;
//	bool			is_child; // `cd /` vs `cd / | cd /`
//	pid_t			pid;
	int				is_last;
}	t_token;

#include "tokenisation.h"
#include "dollar_expand.h"
#include "get_words.h"
#include "get_ftype.h"
#include "get_path.h"
#include "builtins.h"
#include "get_fds.h"

void	free_str_tab(char **tab);

# endif
