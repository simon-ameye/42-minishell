/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:15:23 by sameye            #+#    #+#             */
/*   Updated: 2021/11/25 19:48:13 by sameye           ###   ########.fr       */
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


static t_ftype	get_fnct_type(t_token *tokens)
{
	int i;
	int j;
	static const char* ftypes[] = { "execve", "echo" , "cd", "pwd", "export", "unset", "env", "exit", NULL};

	if (tokens)
	{
		i = 0;
		while (tokens[i].word)
		{
			if (tokens[i].type == WORD)
			{
				tokens[i].type = FUNCTION;
				break;
			}
			i++;
		}
		j = 1;
		while (ftypes[j])
		{
			if (!ft_strcmp(ftypes[j], tokens[i].word))
				return (j);
			j++;
		}
	}
	return (EXECVE);
}


//// Dont forget to exit if just '<'
void	get_token_type(t_proc *proc)
{
	int i;
	int chevronspotted;

	fflush(stdout);
	if (proc->tokens)
	{
		i = 0;
		while (proc->tokens[i].word)
		{
			chevronspotted = 0;
			proc->tokens[i].type = WORD;
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
			if (chevronspotted && !are_alnums(proc->tokens[i + 1].word) && proc->tokens[i + 1].word[0])
				ft_putstr_fd("syntax error near unexpected token", STDERR_FILENO); // Dont forget to exit
			if (chevronspotted && !proc->tokens[i + 1].word)
				ft_putstr_fd("syntax error near unexpected token", STDERR_FILENO); // Dont forget to exit
			else if (chevronspotted && !proc->tokens[i + 1].word[0])
				ft_putstr_fd("ambiguous redirect", STDERR_FILENO); // Dont forget to exit
			i = i + 1 + chevronspotted;
		}
		proc->ftype = get_fnct_type(proc->tokens);
	}
}
