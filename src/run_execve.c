/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 13:25:55 by sameye            #+#    #+#             */
/*   Updated: 2021/12/17 13:28:48 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_execve(t_proc *proc, t_proc *procs)
{
	int		i;
	int		j;
	char	**arg;

	i = 0;
	while (proc->tokens[i].word)
		i++;
	arg = malloc(sizeof(char *) * (i + 1));
	if (!arg)
		exit_minishell(procs, procs->env);
	i = 0;
	j = 0;
	while (proc->tokens[i].word)
	{
		if (proc->tokens[i].type == WORD
			|| proc->tokens[i].type == FUNCTION)
			arg[j++] = proc->tokens[i].word;
		i++;
	}
	arg[j] = NULL;
	if (proc->path && execve(proc->path, arg, *proc->env) == -1)
		perror("minishell");
	free(arg);
}
