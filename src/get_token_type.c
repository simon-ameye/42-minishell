/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:15:23 by sameye            #+#    #+#             */
/*   Updated: 2021/12/17 16:42:57 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;

static int	print_error_near_token(char *word)
{
	ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
	ft_putstr_fd(word, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_FAILURE);
}

static int	print_syntax_error(void)
{
	ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
	ft_putstr_fd("'newline'\n", STDOUT_FILENO);
	return (EXIT_FAILURE);
}

static int	get_filenames_type(t_proc *proc)
{
	int	i;

	if (proc->tokens)
	{
		i = 0;
		while (proc->tokens[i].word)
		{
			if (is_redir_op(proc->tokens[i].type))
			{
				if (!proc->tokens[i + 1].word)
					return (print_syntax_error());
				else if (proc->tokens[i].type == HERE_DOC)
					proc->tokens[i + 1].type = LIMITOR;
				else if (proc->tokens[i + 1].type == IGNORED)
					proc->tokens[i + 1].type = AMBIGOUS_REDIRECT;
				else if (proc->tokens[i + 1].type == WORD)
					proc->tokens[i + 1].type
						= redir_op_to_file_type(proc->tokens[i].type);
				else
					return (print_error_near_token(proc->tokens[i].word));
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
