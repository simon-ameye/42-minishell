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

void	signal_handler(int signum, siginfo_t *siginfo, void *context)
{
	(void)context;
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (siginfo->si_pid != 0)
			rl_redisplay();
		else
			g_exitval = 130;
	}
	else if (signum == SIGQUIT)
	{
		if (siginfo->si_pid == 0)
			ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO); // stderr ?
		else
		{
			write(1, "\b \b", 3);
			write(1, "\b \b", 3);
			g_exitval = 131;
		}
	}
}

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

	// signal setup
	struct sigaction act = {
		.sa_flags = SA_SIGINFO, // allow to call 'sa_sigaction' instead of 'sa_handler'
		.sa_sigaction = &signal_handler
	};
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	rl_outstream = stderr;

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
