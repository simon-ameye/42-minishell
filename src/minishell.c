#include "minishell.h"

unsigned char	g_exitval;

static void	parser(t_proc *procs, char *const *env)
{
	int	i;

	if (procs)
	{
		i = 0;
		while (!procs[i].is_last)
		{

			ft_putstr_fd("\n----------get_token_type----------\n", STDERR_FILENO);
			if (get_token_type(&procs[i])) //out condition inside
				break ;
			print_procs(procs);

			ft_putstr_fd("\n----------dollar_expand----------\n", STDERR_FILENO);
			if(dollar_expand(procs[i], env)) //malloc inside, 
				break ;
			print_procs(procs);

			ft_putstr_fd("\n----------get_fnct_type----------\n", STDERR_FILENO);
			if (get_fnct_type(&procs[i])) //nothing 
				break ;
			print_procs(procs);

			ft_putstr_fd("\n----------remove_quotes----------\n", STDERR_FILENO);
			if (remove_quotes(procs[i])) //malloc inside
				break ;
			print_procs(procs);

			ft_putstr_fd("\n----------get_fds----------\n", STDERR_FILENO);
			if (get_fds(&procs[i])) //nothing
				break ;
			print_procs(procs);

			ft_putstr_fd("\n----------get_path----------\n", STDERR_FILENO);
			if (get_path(&procs[i], env)) //malloc inside,
				break ;
			print_procs(procs);
			i++;
		}
	}
	//
	//exiting in main for tests
	//if (procs[0].ftype == EXIT)
	//	builtin_exit(procs, &(procs[0]));
}

int main(int ac, char **av, char *const *env)
{
	char			*line;
	t_proc			*procs;

	(void)ac;
	(void)av;
	g_exitval = 0;
	(void)g_exitval;
	while (1)
	{
		line = NULL;
		line = readline("\e[0;36mminishell\e[0;35m> \e[0m");
		if (!line)
			break ;
		procs = get_procs(line);
		get_tokens(procs);
		parser(procs, env);
		print_procs(procs);
		free_procs(procs);
		free(line);
	}
	return (0);
}
