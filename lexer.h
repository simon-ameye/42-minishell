#ifndef LEXER_H
# define LEXER_H

typedef enum	e_token_type
{
	NIL,
	COMMAND,
	OPERATOR
}	t_token_type;

typedef struct	s_token
{
	char			*val;
	t_token_type	type;
	void			*next;
}	t_token;

t_token	**lexer(char  *line);
t_token	*new_token(void);
void	lst_print_tokens(t_token **token);
void	lst_clear_tokens(t_token **tokens);
int		add_token(t_token **tokens, t_token *token, char *str);
void	lst_add_token(t_token **tokens, t_token *token);


# endif