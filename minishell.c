#include "minishell.h"

int main()
{
	char	*line;
	t_token	**tokens;

	while (1)
	{
		line = NULL;
		line = readline("minishell> ");
		if (!line)
			break ;
		tokens = lexer(line);
		lst_print_tokens(tokens);
		lst_clear_tokens(tokens);
		free(line);
	}
	return (0);
}
