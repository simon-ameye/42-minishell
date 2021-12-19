/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:16:20 by sameye            #+#    #+#             */
/*   Updated: 2021/12/19 15:02:12 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <limits.h>

# define DO_SKIP 0
# define DO_EXIT 1
# define DO_EXEC 2
# define PROMPT "\e[0;36mminishell\e[0;35m> \e[0m"

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
	WORD,
	FUNCTION,
	FILE_IN,
	HERE_DOC,
	FILE_OUT,
	FILE_OUT_SUR,
	OPEN_FILE,
	LIMITOR,
	EXIT_FILE,
	EXIT_FILE_A,
	IGNORED,
	AMBIGOUS_REDIRECT
}	t_token_type;

typedef struct s_token
{
	char	*word;
	int		type;
	char	*expanded;
}	t_token;

typedef struct s_word
{
	int		len;
	int		start;
	int		op_len;
	int		sp_len;
	char	quote;
}	t_word;

typedef struct s_heredoc
{
	char	*line;
	char	*delimiter;
	char	filename[23];
}	t_heredoc;

typedef struct s_proc
{
	char			*str;
	char			*path;
	char			***env;
	t_token			*tokens;
	t_ftype			ftype;
	int				fdin;
	int				fdout;
	int				stream_in;
	int				stream_out;
	pid_t			pid;
	int				is_last;
	int				saved_std[2];
}	t_proc;

/******************************************************************************/
/*                                                                            */
/*     minishell.c                                                            */
/*                                                                            */
/******************************************************************************/

void	exit_minishell(t_proc *procs, char ***env);

/******************************************************************************/
/*                                                                            */
/*     builtins                                                               */
/*                                                                            */
/******************************************************************************/

void	builtin_cd(t_proc *proc);
void	builtin_exit(t_proc *procs, t_proc *proc);
void	builtin_pwd(void);
void	builtin_env(char **env);
void	builtin_echo(t_proc *proc);
void	builtin_unset(t_proc *proc);
void	builtin_export(t_proc *proc);

/******************************************************************************/
/*                                                                            */
/*     builtins utils                                                         */
/*                                                                            */
/******************************************************************************/

int		get_nb_args(t_token *tokens);
void	skip_n_options(t_token *tokens, int *i, int *n_option);
void	print_env_sort(char **env);

/******************************************************************************/
/*                                                                            */
/*     dollar_expand.c dollar_expand_1.c                                      */
/*                                                                            */
/******************************************************************************/

//char	*dollar_expand_str(char *str, char **env, int heredoc);
//int		dollar_expand(t_proc proc);
//char	*join_char_free(char *str, char c);
//void	threat_dollar_quest_mark(char **res, char **str);
//void	threat_dollar_spec_char(char **res, char **str);
//void	threat_dollar_expand(char **res, char **str, char **env);

/******************************************************************************/
/*                                                                            */
/*     string.c                                                               */
/*                                                                            */
/******************************************************************************/

void	free_str_tab(char **tab);
char	*ft_strjoinfree(char *s1, char *s2);
int		str_tab_len(char *const *env);
int		switch_quote(char *quote, char c);

/******************************************************************************/
/*                                                                            */
/*     get_fds.c                                                              */
/*                                                                            */
/******************************************************************************/

int		get_fds(t_proc *proc, t_proc *procs, char *line);

/******************************************************************************/
/*                                                                            */
/*     get_token_type.c get_token_type_1.c                                    */
/*                                                                            */
/******************************************************************************/

int		get_token_type(t_proc *proc);
int		redir_op_to_file_type(int i);
int		is_redir_op(int i);
void	get_operators(t_proc *proc);

/******************************************************************************/
/*                                                                            */
/*     get_fnct_type.c                                                        */
/*                                                                            */
/******************************************************************************/

void	get_fnct_type(t_proc *proc);

/******************************************************************************/
/*                                                                            */
/*     get_path.c get_path_1.c                                                */
/*                                                                            */
/******************************************************************************/

int		get_path(t_proc *procs);
char	**find_paths(char **env);

/******************************************************************************/
/*                                                                            */
/*     get_tokens.c get_tokens_1.c get_tokens_2.c                             */
/*                                                                            */
/******************************************************************************/

void	get_tokens(t_proc *procs);
int		get_words(t_token *tokens, char *line, t_word word);
int		tokens_nb(t_token *tokens);
void	get_quote_operator_separator(char *line, t_word *word);

/******************************************************************************/
/*                                                                            */
/*     remove_quotes.c                                                        */
/*                                                                            */
/******************************************************************************/

//char	*remove_quotes_str(char *str);
//int		remove_quotes(t_proc proc);

/******************************************************************************/
/*                                                                            */
/*     get_procs.c, get_procs_1.c                                             */
/*                                                                            */
/******************************************************************************/

int		get_nb_procs(char *line);
void	get_procs(t_proc **procs, char *line, char ***env);

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

/******************************************************************************/
/*                                                                            */
/*     env.c                                                                  */
/*                                                                            */
/******************************************************************************/

char	**copy_env(char **original_env);
void	free_env(char ***env);
void	increase_shlvl(char ***env);
void	add_line_in_env(char ***env, char *str);
int		find_var_in_env(char **env, char *str, int strlen);

/******************************************************************************/
/*                                                                            */
/*     here_doc.c                                                             */
/*                                                                            */
/******************************************************************************/

int		get_proc_here_doc(int *fd, t_token token, t_proc *procs, char *line);

/******************************************************************************/
/*                                                                            */
/*     set_ignored_tokens.c                                                   */
/*                                                                            */
/******************************************************************************/

void	set_ignored_tokens(t_proc *proc);

/******************************************************************************/
/*                                                                            */
/*     signals.c                                                              */
/*                                                                            */
/******************************************************************************/

void	init_signals(void);
void	signal_handler(int signum, siginfo_t *siginfo, void *context);

/******************************************************************************/
/*                                                                            */
/*     run_execve.c                                                           */
/*                                                                            */
/******************************************************************************/

void	run_execve(t_proc *proc, t_proc *procs);

/******************************************************************************/
/*                                                                            */
/*     fd_tools                                                               */
/*                                                                            */
/******************************************************************************/

void	close_saved_fd_and_streams(t_proc *procs);
void	secure_close(int fd);
void	close_all_streams_except_current(t_proc *procs, int i);
void	close_std_streams(void);

/******************************************************************************/
/*                                                                            */
/*     remove_quotes_and_expand.c                                             */
/*                                                                            */
/******************************************************************************/
int	remove_quotes_and_expand(t_proc proc);

#endif
