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
	char			*val; // str
	t_token_type	type; // ftype
	void			*next;
}	t_token;

/*
typedef e_function_type
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
	char *const		*env;
	t_function_type	ftype;
	int				input;
	int				output;
	bool			child; // `cd /` vs `cd / | cd /`
	pid_t			pid;
}	t_token;
*/

t_token	**lexer(char  *line);
t_token	*new_token(void);
void	lst_print_tokens(t_token **token);
void	lst_clear_tokens(t_token **tokens);
int		add_token(t_token **tokens, t_token *token, char *str);
void	lst_add_token(t_token **tokens, t_token *token);


# endif