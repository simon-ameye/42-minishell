/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 19:44:18 by trobin            #+#    #+#             */
/*   Updated: 2021/12/21 15:10:12 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;

void	try_chdir(char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		g_exitval = 1;
	}
	else
		g_exitval = 0;
}

void	builtin_cd(t_proc *proc)
{
	int	args;
	int	index;

	if (proc && proc->tokens)
	{
		args = get_nb_args(proc->tokens);
		if (args == 0)
		{
			index = find_var_in_env(*proc->env, "HOME", 4);
			if (index == -1)
			{
				ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
				g_exitval = 0;
			}
			else
				try_chdir((*proc->env)[index] + 5);
		}
		else if (args > 1)
		{
			ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
			g_exitval = 1;
		}
		else if (args == 1)
			try_chdir(proc->tokens[1].word);
	}
}
