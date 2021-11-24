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

/*
typedef struct	s_token
{
	char	*word;
	int		expanded;
}	t_token;

typedef struct	s_io
{
	int		fd;
	char	*filename;
}	t_io;
*/

typedef struct	s_token // s_proc
{
	char			*str;
	char			*path;
	char			**args;
	char			**words;
//	t_token			*tokens;
	t_ftype			ftype;
//	t_io			*in;
//	t_io			*out;
	int				fdin;
	int				fdout;
//	bool			is_child; // `cd /` vs `cd / | cd /`
//	pid_t			pid;
	int				is_last;
}	t_token; // t_proc

/******************************************************************************/
/*                                                                            */
/*     builtins                                                               */
/*                                                                            */
/******************************************************************************/

void	builtin_exit(t_token *tokens, t_token *token);
void	builtin_pwd(t_token *token);
void	builtin_env(char *const *env);

/******************************************************************************/
/*                                                                            */
/*     minishell_utils.c                                                      */
/*                                                                            */
/******************************************************************************/

void	free_str_tab(char **tab);

/******************************************************************************/
/*                                                                            */
/*     dollar_expand.c                                                        */
/*                                                                            */
/******************************************************************************/

char	*find_var(char *str, char *const *env);
void	dollar_expand(t_token *tokens, char *const *env, unsigned char	exitval);
char	*dollar_expand_str(char *str, char *const *env, unsigned char	exitval);
void	strjoin_iter(char **str, char **s1, char **s2);
char	*ft_strjoinfree(char *s1, char *s2);
char	*join_char_free(char *str, char c);

/******************************************************************************/
/*                                                                            */
/*     get_redirs.c                                                           */
/*                                                                            */
/******************************************************************************/

void	get_fds(t_token *tokens);

/******************************************************************************/
/*                                                                            */
/*     get_ftype.c                                                            */
/*                                                                            */
/******************************************************************************/

void    get_ftype(t_token *tokens);
t_ftype get_words_ftype(char *str);

/******************************************************************************/
/*                                                                            */
/*     get_path.c                                                             */
/*                                                                            */
/******************************************************************************/

void    get_path(t_token *tokens, char *const *env);
char	*get_path_iter(char *fnct, char *const *env);
char	**find_paths(char *const *env);

/******************************************************************************/
/*                                                                            */
/*     lexer.c                                                                */
/*                                                                            */
/******************************************************************************/

void    get_words(t_token *tokens);
char	**get_str_words(char *str);

/******************************************************************************/
/*                                                                            */
/*     get_procs.c                                                            */
/*                                                                            */
/******************************************************************************/

char	*custom_ft_strncpy(char *dst, char *src, int len);
char	*ft_strndup(char *s, int n);
void	init_token(t_token *token);
char	*get_token_str(char *line, int token_index);
void	create_token(t_token *tokens, char *line, int index);
int		get_nb_tokens(char *line);
t_token	*tokenisation(char *line);

/******************************************************************************/
/*                                                                            */
/*     print_procs.c                                                         */
/*                                                                            */
/******************************************************************************/

void	print_tokens(t_token *tokens);

/******************************************************************************/
/*                                                                            */
/*     free_procs.c                                                           */
/*                                                                            */
/******************************************************************************/

void	free_tokens(t_token *tokens);

# endif
