#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

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
	char			**env;
	t_token			*tokens;
	t_ftype			ftype;
//	t_io			in;
//	t_io			out;
	int				fdin; // fd_in
	int				fdout; //fd_out
	int				stream_in;
	int				stream_out;
//	bool			is_child; // `cd /` vs `cd / | cd /`
	pid_t			pid;
	int				is_last;
}	t_proc;

/******************************************************************************/
/*                                                                            */
/*     builtins                                                               */
/*                                                                            */
/******************************************************************************/

void	builtin_exit(t_proc *procs, t_proc *proc);
void	builtin_pwd(void);
void	builtin_env(char *const *env);
void	builtin_echo(t_proc *proc);

/******************************************************************************/
/*                                                                            */
/*     dollar_expand.c                                                        */
/*                                                                            */
/******************************************************************************/

int	dollar_expand(t_proc proc);

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

int	get_fds(t_proc *proc);

/******************************************************************************/
/*                                                                            */
/*     get_token_type.c                                                       */
/*                                                                            */
/******************************************************************************/

int    get_token_type(t_proc *proc);

/******************************************************************************/
/*                                                                            */
/*     get_fnct_type.c                                                        */
/*                                                                            */
/******************************************************************************/

int	get_fnct_type(t_proc *proc);

/******************************************************************************/
/*                                                                            */
/*     get_path.c                                                             */
/*                                                                            */
/******************************************************************************/

int    get_path(t_proc *procs);

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

int	remove_quotes(t_proc proc);

/******************************************************************************/
/*                                                                            */
/*     get_procs.c                                                            */
/*                                                                            */
/******************************************************************************/

void	get_procs(t_proc **procs, char *line, char **env);

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
void	free_tokens(t_token *tokens);

/******************************************************************************/
/*                                                                            */
/*     exec.c                                                                 */
/*                                                                            */
/******************************************************************************/

void	exec(t_proc *procs);

/******************************************************************************/
/*                                                                            */
/*     exec_child.c                                                           */
/*                                                                            */
/******************************************************************************/

void	exec_child(t_proc *proc, t_proc *procs);

# endif
