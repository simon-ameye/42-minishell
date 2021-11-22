#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	int	i;
	int j;

	i = 0;
	if (tokens)
	{
		while(!tokens[i].is_last)
		{
			if (tokens[i].str)
			{
				printf("process: %d\n", i);
				printf("	words : ");
				j = 0;
				while(tokens[i].words[j])
				{
					printf("[%s]", tokens[i].words[j]);
					j++;
				}
				printf("\n");
				printf("	ftype : %i", tokens[i].ftype);
				printf("	str: %s\n", tokens[i].str);
			}
			i++;
		}
	}
}
