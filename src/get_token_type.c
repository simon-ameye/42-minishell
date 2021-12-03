/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:15:23 by sameye            #+#    #+#             */
/*   Updated: 2021/12/03 16:45:59 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;

static int are_alnums(char *s)
{
	if (s)
	{
		while (*s)
		{
			if (!ft_isalnum(*s))
				return (0);
			s++;
		}
	}
	return (1);
}

int	get_token_type(t_proc *proc)
{
	int i;
	int chevron;
	int	error;

	error = 0;
	if (proc->tokens)
	{
		i = 0;
		while (proc->tokens[i].word)
		{
			chevron = 0;
			proc->tokens[i].type = WORD;
			if (!ft_strcmp(proc->tokens[i].word, "<"))
			{
				proc->tokens[i].type = FILE_IN;
				proc->tokens[i + 1].type = OPEN_FILE;
				chevron = 1;
			}
			else if (!ft_strcmp(proc->tokens[i].word, "<<"))
			{
				proc->tokens[i].type = HERE_DOC;
				proc->tokens[i + 1].type = LIMITOR;
				chevron = 1;
			}
			else if (!ft_strcmp(proc->tokens[i].word, ">"))
			{
				proc->tokens[i].type = FILE_OUT;
				proc->tokens[i + 1].type = EXIT_FILE;
				chevron = 1;
			}
			else if (!ft_strcmp(proc->tokens[i].word, ">>"))
			{
				proc->tokens[i].type = FILE_OUT_SUR;
				proc->tokens[i + 1].type = EXIT_FILE_RET;
				chevron = 1;
			}
			error = 1;
			if (chevron && !proc->tokens[i + 1].word)
				ft_putstr_fd("syntax error near unexpected token\n", STDERR_FILENO);
			else if (chevron
				&& !are_alnums(proc->tokens[i + 1].word)
				&& proc->tokens[i + 1].word[0]
				&& proc->tokens[i+1].type != LIMITOR)
				ft_putstr_fd("syntax error near unexpected token\n", STDERR_FILENO);
			else if (chevron && !proc->tokens[i + 1].word[0])
				ft_putstr_fd("ambiguous redirect\n", STDERR_FILENO);
			else
				error = 0;
			if (error == 1)
			{
				g_exitval = 2;
				return (EXIT_FAILURE);
			}
			i = i + 1 + chevron;
		}
	}
	return (EXIT_SUCCESS);
}
