/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ftype.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:15:23 by sameye            #+#    #+#             */
/*   Updated: 2021/11/25 12:32:33 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ftype	get_words_ftype(char *str)
{
	int i;
	static const char* ftypes[] = { "execve", "echo" , "cd", "pwd", "export", "unset", "env", "exit", NULL};

	i = 1;
	while (ftypes[i])
	{
		if (!ft_strcmp(ftypes[i], str))
			return (i);
		i++;
	}
	return (EXECVE);
}

void	get_ftype(t_proc *proc)
{
	if (proc)
	{
		if (proc->tokens)
			proc->ftype = get_words_ftype(proc->tokens[0].word);
	}
}
