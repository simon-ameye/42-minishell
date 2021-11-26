#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	int	i;

	if (tokens)
	{
		i = 0;
		while (tokens[i].word)
		{
			free(tokens[i].word);
			i++;
		}
		free(tokens);
		tokens = NULL;
	}
}

void	free_procs(t_proc *procs)
{
	int	i;

	i = 0;
	if (procs)
	{
		while(!procs[i].is_last)
		{
			if (procs[i].str)
				free(procs[i].str);
			if (procs[i].path)
				free(procs[i].path);
			if (procs[i].tokens)
				free_tokens(procs[i].tokens);
			i++;
		}
		free(procs);
		procs = NULL;
	}
}
