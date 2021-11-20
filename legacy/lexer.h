#ifndef LEXER_H
# define LEXER_H

//#include "minishell.h"

t_token	**lexer(char  *line);
t_token	*new_token(void);
void	lst_print_tokens(t_token **token);
void	lst_clear_tokens(t_token **tokens);
int		add_token(t_token **tokens, t_token *token, char *str);
void	lst_add_token(t_token **tokens, t_token *token);


# endif
