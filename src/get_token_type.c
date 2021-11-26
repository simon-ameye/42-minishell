/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:15:23 by sameye            #+#    #+#             */
/*   Updated: 2021/11/26 12:14:20 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//// Dont forget to exit if just '<'
void	get_token_type(t_proc *proc)
{
	int i;
	int chevronspotted;

	if (proc->tokens)
	{
		i = 0;
		while (proc->tokens[i].word)
		{
			chevronspotted = 0;
			proc->tokens[i].type = WORD;
			//if (proc->tokens[i].expanded == 0)
			//{
				if (!ft_strcmp(proc->tokens[i].word, "<"))
				{
					proc->tokens[i].type = FILE_IN;
					proc->tokens[i + 1].type = OPEN_FILE;
					chevronspotted = 1;
				}
				else if (!ft_strcmp(proc->tokens[i].word, "<<"))
				{
					proc->tokens[i].type = HERE_DOC;
					proc->tokens[i + 1].type = LIMITOR;
					chevronspotted = 1;
				}
				else if (!ft_strcmp(proc->tokens[i].word, ">"))
				{
					proc->tokens[i].type = FILE_OUT;
					proc->tokens[i + 1].type = EXIT_FILE;
					chevronspotted = 1;
				}
				else if (!ft_strcmp(proc->tokens[i].word, ">>"))
				{
					proc->tokens[i].type = FILE_OUT_SUR;
					proc->tokens[i + 1].type = EXIT_FILE_RET;
					chevronspotted = 1;
				}
			//}
			if (chevronspotted && !are_alnums(proc->tokens[i + 1].word) && proc->tokens[i + 1].word[0])
				ft_putstr_fd("syntax error near unexpected token\n", STDERR_FILENO); // Dont forget to free + exit
			if (chevronspotted && !proc->tokens[i + 1].word)
				ft_putstr_fd("syntax error near unexpected token\n", STDERR_FILENO); // Dont forget to exit
			else if (chevronspotted && !proc->tokens[i + 1].word[0])
				ft_putstr_fd("ambiguous redirect\n", STDERR_FILENO); // Dont forget to exit
			i = i + 1 + chevronspotted;
		}
	}
}
