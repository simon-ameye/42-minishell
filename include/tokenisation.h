#ifndef TOKENISATION_H
# define TOKENISATION_H

char	*custom_ft_strncpy(char *dst, char *src, int len);
char	*ft_strndup(char *s, int n);
void	init_token(t_token *token);
char	*get_token_str(char *line, int token_index);
void	create_token(t_token *tokens, char *line, int index);
int		get_nb_tokens(char *line);
t_token	*tokenisation(char *line);

//		print_tokens.c
void	print_tokens(t_token *tokens);

//		free_tokens.c
void	free_tokens(t_token *tokens);

# endif
