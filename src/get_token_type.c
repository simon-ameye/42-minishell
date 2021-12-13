/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:15:23 by sameye            #+#    #+#             */
/*   Updated: 2021/12/13 16:58:04 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;

/*
static int is_filename(char *s)
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
				&& !is_filename(proc->tokens[i + 1].word)
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
*/

static void	get_operators(t_proc *proc)
{
	int i;

	if (proc->tokens)
	{
		i = 0;
		while (proc->tokens[i].word)
		{
			//proc->tokens[i].type = WORD;
			if (!proc->tokens[i].expanded)
			{
				if (!ft_strcmp(proc->tokens[i].word, "<"))
					proc->tokens[i].type = FILE_IN;
				else if (!ft_strcmp(proc->tokens[i].word, "<<"))
					proc->tokens[i].type = HERE_DOC;
				else if (!ft_strcmp(proc->tokens[i].word, ">"))
					proc->tokens[i].type = FILE_OUT;
				else if (!ft_strcmp(proc->tokens[i].word, ">>"))
					proc->tokens[i].type = FILE_OUT_SUR;
			}
			i++;
		}
	}
}

static int	is_redir_op(int i)
{
	return (i == FILE_IN
				|| i == HERE_DOC
				|| i == FILE_OUT
				|| i == FILE_OUT_SUR);
}

static int	redir_op_to_file_type(int i)
{
	return ((i == FILE_IN) * OPEN_FILE
				+ (i == HERE_DOC) * LIMITOR
				+ (i == FILE_OUT) * EXIT_FILE
				+ (i == FILE_OUT_SUR) * EXIT_FILE_RET);
}

static int	get_filenames_type(t_proc *proc)
{
	int i;

	if (proc->tokens)
	{
		i = 0;
		while (proc->tokens[i].word)
		{
			if (is_redir_op(proc->tokens[i].type))
			{
				if (!proc->tokens[i + 1].word)
				{
					ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
					ft_putstr_fd("'newline'\n", STDOUT_FILENO);
					return (EXIT_FAILURE);
				}
				else if (proc->tokens[i].type == HERE_DOC)
					proc->tokens[i + 1].type = LIMITOR;
				else if (proc->tokens[i + 1].type == IGNORED)
				{
					//ft_putstr_fd("ambiguous redirect\n", STDERR_FILENO);
					proc->tokens[i + 1].type = AMBIGOUS_REDIRECT;
				}
				else if (proc->tokens[i + 1].type == WORD)
					proc->tokens[i + 1].type = redir_op_to_file_type(proc->tokens[i].type);
				else //There is probably an other redir next to this one
				{
					ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
					ft_putstr_fd(proc->tokens[i].word, STDOUT_FILENO);
					ft_putstr_fd("\n", STDOUT_FILENO);
					return (EXIT_FAILURE);
				}
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

int	get_token_type(t_proc *proc)
{
	get_operators(proc);
	return (get_filenames_type(proc));
}
