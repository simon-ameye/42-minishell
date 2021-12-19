/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:25:13 by trobin            #+#    #+#             */
/*   Updated: 2021/12/19 20:52:52 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	g_exitval;

void	exit_minishell(t_proc *procs, char ***env)
{
	free_env(env);
	close_saved_fd_and_streams(procs);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	free_procs(procs);
	rl_clear_history();
	exit(g_exitval);
}

static int	parser(t_proc *procs, char *line)
{
	int	i;

	if (!procs)
		return (DO_SKIP);
	i = 0;
	while (!procs[i].is_last)
	{
		if (get_token_type(&procs[i]))
			return (DO_SKIP);
		if (remove_quotes_and_expand(procs[i]))
			return (DO_EXIT);
		get_fnct_type(&procs[i]);
		if (get_fds(&procs[i], procs, line))
			procs[i].ftype = NO_FUNCTION;
		if (get_path(&procs[i]))
			procs[i].ftype = NO_FUNCTION;
		i++;
	}
	return (DO_EXEC);
}

static void	interpreter(t_proc *procs, char ***env, char *line)
{
	int	action;

	get_procs(&procs, line, env);
	get_tokens(procs);
	action = parser(procs, line);
	if (action == DO_EXIT)
	{
		free(line);
		exit_minishell(procs, env);
	}
	if (action == DO_SKIP)
	{
		add_history(line);
		free(line);
		free_procs(procs);
		return ;
	}
	if (action == DO_EXEC)
	{
		add_history(line);
		free(line);
		exec(procs);
	}
}

static void	init_minishell(int ac, char **av, char ***env, char **envp)
{
	(void)ac;
	(void)av;
	g_exitval = 0;
	*env = copy_env(envp);
	if (*env == NULL)
	{
		ft_putstr_fd("minishell: error: malloc fail\n", STDERR_FILENO);
		exit_minishell(NULL, env);
	}
	init_signals();
	rl_outstream = stderr;
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	**env;
	t_proc	*procs;

	init_minishell(ac, av, &env, envp);
	while (1)
	{
		line = NULL;
		line = readline(PROMPT);
		if (!line)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			exit_minishell(NULL, &env);
		}
		else if (*line)
		{
			procs = NULL;
			interpreter(procs, &env, line);
		}
	}
	return (0);
}
