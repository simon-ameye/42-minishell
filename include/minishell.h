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

# define PRINT 1

typedef enum e_ftype
{
	EXECVE,
	NO_FUNCTION,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_ftype;

typedef enum e_token_type
{
    WORD,			//word
	FUNCTION,		//function
    FILE_IN,		//'<'
    HERE_DOC,		//<<'
    FILE_OUT,		//'>'
    FILE_OUT_SUR,	//'>>'
    OPEN_FILE,		// word following '<'
    LIMITOR,		// word following '<<'
    EXIT_FILE,		// word following '>'
    EXIT_FILE_RET	// word following '>>'
}	t_token_type;

typedef struct	s_token
{
	char	*word;
	int		type;
}	t_token;

/*
typedef struct	s_io
{
	int		fd;
	char	*filename;
	void	*next;
}	t_io;
*/

typedef struct	s_proc
{
	char			*str;
	char			*path;
	char			**args;
//	char			**words;
	t_token			*tokens;
	t_ftype			ftype;
//	t_io			in;
//	t_io			out;
	int				fdin;
	int				fdout;
//	bool			is_child; // `cd /` vs `cd / | cd /`
//	pid_t			pid;
	int				is_last;
}	t_proc;

/******************************************************************************/
/*                                                                            */
/*     builtins                                                               */
/*                                                                            */
/******************************************************************************/

void	builtin_exit(t_proc *procs, t_proc *proc);
void	builtin_pwd(t_proc *proc);
void	builtin_env(char *const *env);

/******************************************************************************/
/*                                                                            */
/*     dollar_expand.c                                                        */
/*                                                                            */
/******************************************************************************/

void	dollar_expand(t_proc proc, char *const *env);

/******************************************************************************/
/*                                                                            */
/*     string.c                                                               */
/*                                                                            */
/******************************************************************************/

void	free_str_tab(char **tab);
char	*ft_strjoinfree(char *s1, char *s2);
char	*join_char_free(char *str, char c);

/******************************************************************************/
/*                                                                            */
/*     get_redirs.c                                                           */
/*                                                                            */
/******************************************************************************/

void	get_fds(t_proc *proc);

/******************************************************************************/
/*                                                                            */
/*     get_token_type.c                                                       */
/*                                                                            */
/******************************************************************************/

void    get_token_type(t_proc *proc);

/******************************************************************************/
/*                                                                            */
/*     get_fnct_type.c                                                        */
/*                                                                            */
/******************************************************************************/

void	get_fnct_type(t_proc *proc);

/******************************************************************************/
/*                                                                            */
/*     get_path.c                                                             */
/*                                                                            */
/******************************************************************************/

void    get_path(t_proc *procs, char *const *env);

/******************************************************************************/
/*                                                                            */
/*     get_tokens.c                                                           */
/*                                                                            */
/******************************************************************************/

void    get_tokens(t_proc *procs);

/******************************************************************************/
/*                                                                            */
/*     remove_quotes.c                                                        */
/*                                                                            */
/******************************************************************************/

void	remove_quotes(t_proc proc);

/******************************************************************************/
/*                                                                            */
/*     get_procs.c                                                            */
/*                                                                            */
/******************************************************************************/

char	*custom_ft_strncpy(char *dst, char *src, int len);
char	*ft_strndup(char *s, int n);
void	init_proc(t_proc *proc);
char	*get_proc_str(char *line, int proc_index);
void	create_proc(t_proc *procs, char *line, int index);
int		get_nb_procs(char *line);
t_proc	*get_procs(char *line);

/******************************************************************************/
/*                                                                            */
/*     print_procs.c                                                         */
/*                                                                            */
/******************************************************************************/

void	print_procs(t_proc *procs);

/******************************************************************************/
/*                                                                            */
/*     free_procs.c                                                           */
/*                                                                            */
/******************************************************************************/

void	free_procs(t_proc *procs);

# endif
