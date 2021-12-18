/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ignored_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:23:22 by trobin            #+#    #+#             */
/*   Updated: 2021/12/18 14:23:29 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_ignored_tokens(t_proc *proc)
{
	int	i;

	if (proc->tokens)
	{
		i = 0;
		while (proc->tokens[i].word)
		{
			if (proc->tokens[i].word[0] == '\0')
				proc->tokens[i].type = IGNORED;
			i++;
		}
	}
}
