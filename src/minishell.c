#include "minishell.h"

int main(int ac, char **av, char *const *env)
{
	char			*line;
	t_token			*tokens;
	unsigned char	exitval;

	(void)ac;
	(void)av;
	exitval = 0;
	while (1)
	{
		line = NULL;
		line = readline("minishell> ");
		if (!line)
			break ;
		tokens = tokenisation(line);
		get_words(tokens);
		dollar_expand(tokens, env, exitval);
		get_ftype(tokens);
		get_path(tokens, env);
		print_tokens(tokens);
		//exiting in main for tests
		if (tokens[0].ftype == EXIT)
			builtin_exit(tokens, &(tokens[0]));
		free_tokens(tokens);
		free(line);
	}
	return (0);
}
