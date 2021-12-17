/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fnct_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 13:57:20 by sameye            #+#    #+#             */
/*   Updated: 2021/12/17 14:00:49 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_function_token(t_token *tokens, int *i)
{
	while (tokens[*i].word)
	{
		if (tokens[*i].type == WORD)
		{
			tokens[*i].type = FUNCTION;
			break ;
		}
		i++;
	}
}

static t_ftype	get_fnct_type_from_token(t_token *tokens)
{
	int					i;
	int					j;
	static const char	*ftypes[] = {"execve", "no_function", "echo",
		"cd", "pwd", "export", "unset", "env", "exit", NULL};

	if (tokens)
	{
		i = 0;
		find_function_token(tokens, &i);
		if (tokens[i].word)
		{
			j = 2;
			while (ftypes[j])
			{
				if (!ft_strcmp(ftypes[j], tokens[i].word))
					return (j);
				j++;
			}
		}
		else
			return (NO_FUNCTION);
	}
	return (EXECVE);
}

void	get_fnct_type(t_proc *proc)
{
	if (proc->tokens)
		proc->ftype = get_fnct_type_from_token(proc->tokens);
}
