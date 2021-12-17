/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 19:46:28 by trobin            #+#    #+#             */
/*   Updated: 2021/12/17 20:14:31 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;

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

static void	exit_too_many_arguments(t_proc *proc)
{
	if (proc->pid)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	g_exitval = 1;
}

static void	exit_non_numeric_arguments(t_proc *proc, t_proc *procs)
{
	if (proc->pid)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(proc->tokens[1].word, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	g_exitval = 2;
	exit_minishell(procs, proc->env);
}

void	builtin_exit(t_proc *proc, t_proc *procs)
{
	int		exit_args;
	long	exit_value;

	exit_args = get_nb_args(proc->tokens);
	if (exit_args == 0)
	{
		if (proc->pid)
			ft_putstr_fd("exit\n", STDERR_FILENO);
		exit_minishell(procs, procs->env);
	}
	else
	{
		exit_value = ft_atol(proc->tokens[1].word);
		if (exit_value == -1)
			return (exit_non_numeric_arguments(proc, procs));
		if (exit_args > 1)
			return (exit_too_many_arguments(proc));
		if (proc->pid)
			ft_putstr_fd("exit\n", STDERR_FILENO);
		g_exitval = (unsigned char)exit_value;
		exit_minishell(procs, procs->env);
	}
}
