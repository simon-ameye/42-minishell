#include "minishell.h"

static void	parser(t_proc *procs, char *const *env, unsigned char exitval)
{
	int	i;

	if (procs)
	{
		i = 0;
		while (!procs[i].is_last)
		{
			dollar_expand(procs[i], env, exitval);
			get_token_type(&procs[i]); // merge two funtions
			get_path(&procs[i], env);
			i++;
		}
	}
	//get_fds(procs);
	//exiting in main for tests
	//if (procs[0].ftype == EXIT)
	//	builtin_exit(procs, &(procs[0]));
}

int main(int ac, char **av, char *const *env)
{
	char			*line;
	t_proc			*procs;
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
		procs = get_procs(line);
		get_tokens(procs);
		parser(procs, env, exitval);
		print_procs(procs);
		free_procs(procs);
		free(line);
	}
	return (0);
}
