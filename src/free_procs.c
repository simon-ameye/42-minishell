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
			if (tokens[i].expanded) //Il suffisait de free le .expanded
				free(tokens[i].expanded);
			i++;
		}
		free(tokens);
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
	}
}
