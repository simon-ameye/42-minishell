#ifndef TOKENISATION_H
# define TOKENISATION_H

char	*custom_ft_strncpy(char *dst, char *src, int len);
char	*ft_strndup(char *s, int n);
void	init_token(t_token *token, char *const *env);
void	free_tokens(t_token *tokens);
char	*get_token_str(char *line, int token_index);
void	create_token(t_token *tokens, char *line, int index, char *const *env);
void	print_tokens(t_token *tokens);
int		get_nb_tokens(char *line);
t_token	*tokenisation(char *line, char *const *env);

# endif
