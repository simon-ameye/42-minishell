#include "minishell.h"

# define SKIP 0
# define EXIT 1
# define EXEC 2
# define PROMPT "\e[0;36mminishell\e[0;35m> \e[0m"

unsigned char	g_exitval;

static int	parser(t_proc *procs, char *line)
{
	int	i;

	if (!procs)
		return (EXIT_FAILURE);
	i = 0;
	while (!procs[i].is_last)
	{
		if (dollar_expand(procs[i]))
			return (EXIT);
		set_ignored_tokens(&procs[i]);
		if (get_token_type(&procs[i]))
			return (SKIP);
		if (remove_quotes(procs[i]))
			return (EXIT);
		get_fnct_type(&procs[i]);
		if (get_fds(&procs[i], procs, line))
			procs[i].ftype = NO_FUNCTION;
		if (get_path(&procs[i]))
			procs[i].ftype = NO_FUNCTION;
		i++;
	}
	return (EXEC);
}

static void	interpreter(t_proc **procs, char ***env, char *line)
{
	int	action;

	*procs = NULL; // ?
	get_procs(procs, line, env);
	get_tokens(*procs);
	action = parser(*procs, line);
	if (action == EXIT)
	{
		free(line);
		exit_minishell(*procs, env);
	}
	if (action == SKIP)
	{
		add_history(line);
		free(line);
		free_procs(*procs);
		return ;
	}
	if (action == EXEC)
	{
		add_history(line);
		free(line);
		exec(*procs);
	}
}

void	init_minishell(t_proc **procs, char ***env, char **envp)
{
	g_exitval = 0;
	*procs = NULL;
	*env = copy_env(envp);
	if (*env == NULL)
	{
		ft_putstr_fd("minishell: error: malloc fail\n", STDERR_FILENO);
		exit_minishell(*procs, env);
	}
	init_signals();
	rl_outstream = stderr; // we should redirect input also !...
	//increase_shlvl(&env);
}

int main(int ac, char **av, char **envp)
{
	char	*line;
	char	**env;
	t_proc	*procs;

	(void)ac;
	(void)av;
	init_minishell(&procs, &env, envp);
	while (1)
	{
		line = NULL;
		line = readline(PROMPT);
		if (!line) // EOF. readline can't fail (cf. man readline)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			exit_minishell(NULL, &env);
		}
		else if (*line)
			interpreter(&procs, &env, line);
	}
	return (0);
}
