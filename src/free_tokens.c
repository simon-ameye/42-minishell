#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	if (tokens)
	{
		while(!tokens[i].is_last)
		{
			if (tokens[i].str)
				free(tokens[i].str);
			if (tokens[i].words)
				free_str_tab(tokens[i].words);
			if (tokens[i].path)
				free(tokens[i].path);
			i++;
		}
		free(tokens);
	}
}
