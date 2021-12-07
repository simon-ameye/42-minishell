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

			//forcement apres get_token_type
			if(dollar_expand(procs[i])) //malloc inside, 
				return (EXIT_FAILURE);

			//forcement apres dollar_expand
			if(set_ignored_tokens(&procs[i])) //malloc inside, 
				return (EXIT_FAILURE);

			//forcement apres set_ignored_tokens
			if (get_token_type(&procs[i])) //out condition inside
				return (EXIT_FAILURE);

			//forcement apres set_ignored_tokens
			if (remove_quotes(procs[i])) //malloc inside
				return (EXIT_FAILURE);

			//forcement apres remove_quotes
			//forcement apres dollar_expand
			if (get_fnct_type(&procs[i])) //nothing 
				return (EXIT_FAILURE);

			//forcement apres get_token_type
			if (get_fds(&procs[i])) //nothing
				return (EXIT_FAILURE);

			//forcement apres get_fnct_type
			if (get_path(&procs[i])) //malloc inside,
				return (EXIT_FAILURE);

			//print_procs(procs);
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

int main(int ac, char **av, char **envp)
{
	char	*line;
	char	**env;
	t_proc	*procs;

	(void)ac;
	(void)av;
	g_exitval = 0;
	env = copy_env(envp);
	increase_shlvl(&env);
	init_signals();
	while (1)
	{
		line = NULL;
		line = readline("\e[0;36mminishell\e[0;35m> \e[0m");
		if (!line) // EOF. readline can't fail (cf. man readline)
		{
			write(1, "exit\n", 5);
			exit(g_exitval);
		}
		else if (*line)
		{
			add_history(line);
			procs = NULL;
			get_procs(&procs, line, &env);
			free(line);
			get_tokens(procs);
			if (!parser(procs))
				exec(procs);
		}
	}
	free_env(&env);
	return (0);
}
