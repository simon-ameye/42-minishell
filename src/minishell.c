#include "minishell.h"

int main(int ac, char **av, char *const *env)
{
	char	*line;
	t_token	*tokens;

	(void)ac;
	(void)av;
	while (1)
	{
		line = NULL;
		line = readline("minishell> ");
		if (!line)
			break ;
		tokens = tokenisation(line);
		get_words(tokens);
		dollar_expand(tokens, env);
		get_ftype(tokens);
		get_path(tokens, env);
		print_tokens(tokens);
		free_tokens(tokens);
		free(line);
	}
	return (0);
}
