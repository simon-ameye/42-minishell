#include "minishell.h"

void	print_procs(t_proc *procs)
{
	int	i;
	int j;

	if (procs)
	{
		i = 0;
		while (!procs[i].is_last)
		{
			if (procs[i].str)
			{
				printf("process: %d\n", i);
				printf("	str: [%s]\n", procs[i].str);
			}
			if (procs[i].tokens)
			{
				printf("	token words : ");
				j = 0;
				while (procs[i].tokens[j].word)
				{
					printf("[%s]", procs[i].tokens[j].word);
					//printf("(%d)", procs[i].tokens[j].expanded);
					printf("{%d} ", procs[i].tokens[j].type);
					j++;
				}
				printf("\n");
			}
			printf("	ftype : %i\n", procs[i].ftype);
			printf("	path : %s\n", procs[i].path);
			printf("	fd_in: %d, fd_out: %d\n", procs[i].fdin, procs[i].fdout);
			printf("	stream_in: %d, stream_out: %d\n", procs[i].stream_in, procs[i].stream_out);
			/*
			if (procs[i].path)
				printf("	path : %s\n", procs[i].path);
			printf("	fds : in : %d out : %d\n", procs[i].fdin, procs[i].fdout);
			*/
			fflush(stdout);
			i++;
		}
	}
}
