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
			{
				free(tokens[i].str);
				free_words(tokens[i].words);
			}
			i++;
		}
		free(tokens);
	}
}
