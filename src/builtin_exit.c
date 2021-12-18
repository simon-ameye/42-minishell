/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 19:46:28 by trobin            #+#    #+#             */
/*   Updated: 2021/12/18 12:10:46 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;

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

static void	get_sign(char *s, int *sign, int *i)
{
	*sign = 1;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

static unsigned long	get_exit_value(char *s, t_proc *proc, t_proc *procs)
{
	unsigned long	ret;
	int				i;
	int				sign;

	if (!s)
		exit_non_numeric_arguments(proc, procs);
	i = 0;
	while (s[i] == ' ')
		i++;
	if (!s[i])
		exit_non_numeric_arguments(proc, procs);
	get_sign(s, &sign, &i);
	ret = 0;
	while (ft_isdigit(s[i]))
	{
		ret = ret * 10 + s[i] - 48;
		if ((sign == 1 && ret > LONG_MAX)
			|| (sign == -1 && ret > (unsigned long)(LONG_MAX + 1UL)))
			exit_non_numeric_arguments(proc, procs);
		i++;
	}
	if (s[i])
		exit_non_numeric_arguments(proc, procs);
	return ((long)(ret * sign));
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
		exit_value = get_exit_value(proc->tokens[1].word, proc, procs);
		if (exit_args > 1)
			return (exit_too_many_arguments(proc));
		if (proc->pid)
			ft_putstr_fd("exit\n", STDERR_FILENO);
		g_exitval = (unsigned char)exit_value;
		exit_minishell(procs, procs->env);
	}
}
