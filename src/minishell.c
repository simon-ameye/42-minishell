#include "minishell.h"

static void	parser(t_proc *procs, char *const *env, unsigned char exitval)
{
	int	i;

	if (procs)
	{
		i = 0;
		while (!procs[i].is_last)
		{
			ft_putstr_fd("\n----------get_token_type----------\n", STDERR_FILENO);
			get_token_type(&procs[i]);
			print_procs(procs);

			ft_putstr_fd("\n----------dollar_expand----------\n", STDERR_FILENO);
			dollar_expand(procs[i], env, exitval);
			print_procs(procs);

			ft_putstr_fd("\n----------get_fnct_type----------\n", STDERR_FILENO);
			get_fnct_type(&procs[i]);
			print_procs(procs);

			ft_putstr_fd("\n----------remove_quotes----------\n", STDERR_FILENO);
			remove_quotes(procs[i]);
			print_procs(procs);

			ft_putstr_fd("\n----------get_fds----------\n", STDERR_FILENO);
			get_fds(&procs[i]);
			print_procs(procs);

			ft_putstr_fd("\n----------get_path----------\n", STDERR_FILENO);
			get_path(&procs[i], env);
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
