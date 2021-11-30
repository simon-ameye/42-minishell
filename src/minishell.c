#include "minishell.h"

unsigned char	g_exitval;

static int	parser(t_proc *procs)
{
	int	i;

	if (procs)
	{
		i = 0;
		while (!procs[i].is_last)
		{

	//		ft_putstr_fd("\n----------get_token_type----------\n", STDERR_FILENO);
			if (get_token_type(&procs[i])) //out condition inside
				return (EXIT_FAILURE);
	//		print_procs(procs);

	//		ft_putstr_fd("\n----------dollar_expand----------\n", STDERR_FILENO);
			if(dollar_expand(procs[i])) //malloc inside, 
				return (EXIT_FAILURE);
	//		print_procs(procs);

	//		ft_putstr_fd("\n----------get_fnct_type----------\n", STDERR_FILENO);
			if (get_fnct_type(&procs[i])) //nothing 
				return (EXIT_FAILURE);
	//		print_procs(procs);

	//		ft_putstr_fd("\n----------remove_quotes----------\n", STDERR_FILENO);
			if (remove_quotes(procs[i])) //malloc inside
				return (EXIT_FAILURE);
	//		print_procs(procs);

	//		ft_putstr_fd("\n----------get_fds----------\n", STDERR_FILENO);
			if (get_fds(&procs[i])) //nothing
				return (EXIT_FAILURE);
	//		print_procs(procs);

	//		ft_putstr_fd("\n----------get_path----------\n", STDERR_FILENO);
			if (get_path(&procs[i])) //malloc inside,
				return (EXIT_FAILURE);
			print_procs(procs);
			i++;
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/*
static int	parser(t_proc *procs, char *const *env)
{
	int	i;

	if (procs)
	{
		i = 0;
		while (!procs[i].is_last)
		{
			if (get_token_type(&procs[i]))
				break ;
			if (dollar_expand(procs[i], env))
				break ;
			if (get_fnct_type(&procs[i]))
				break ;
			if (remove_quotes(procs[i]))
				break ;
			if (get_fds(&procs[i]))
				break ;
			if (get_path(&procs[i], env))
				break ;
			i++;
		}
	}
	return (!procs || !procs[i].is_last);
}
*/

int main(int ac, char **av, char *const *original_env)
{
	char			*line;
	t_proc			*procs;
	char 			**env;

	(void)ac;
	(void)av;
	g_exitval = 0;
	env = copy_env(original_env);
	while (1)
	{
		line = NULL;
		line = readline("\e[0;36mminishell\e[0;35m> \e[0m");
		if (!line)
			break ;
		add_history(line);
		procs = NULL;
		get_procs(&procs, line, env);
		free(line);
		get_tokens(procs);
		if (!parser(procs))
			exec(procs);
		//print_procs(procs);
	}
	free_str_tab(env);
	return (0);
}
