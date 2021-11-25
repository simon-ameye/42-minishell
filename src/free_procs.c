#include "minishell.h"

void	free_procs(t_proc *procs)
{
	int	i;
	int	j;

	i = 0;
	if (procs)
	{
		while(!procs[i].is_last)
		{
			if (procs[i].str)
				free(procs[i].str);
			if (procs[i].tokens)
			{
				//free_str_tab(procs[i].words);
				j = 0;
				while (procs[i].tokens[j].word)
				{
					free(procs[i].tokens[j].word);
					j++;
				}
				free(procs[i].tokens);
			}
			if (procs[i].path)
				free(procs[i].path);
			i++;
		}
		free(procs);
	}
}
