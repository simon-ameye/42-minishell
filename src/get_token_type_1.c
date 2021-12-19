/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:36:40 by sameye            #+#    #+#             */
/*   Updated: 2021/12/19 13:14:01 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_operators(t_proc *proc)
{
	int	i;

	if (proc->tokens)
	{
		i = 0;
		while (proc->tokens[i].word)
		{
			//if (!proc->tokens[i].expanded)
			//{
			if (!ft_strcmp(proc->tokens[i].word, "<"))
				proc->tokens[i].type = FILE_IN;
			else if (!ft_strcmp(proc->tokens[i].word, "<<"))
				proc->tokens[i].type = HERE_DOC;
			else if (!ft_strcmp(proc->tokens[i].word, ">"))
				proc->tokens[i].type = FILE_OUT;
			else if (!ft_strcmp(proc->tokens[i].word, ">>"))
				proc->tokens[i].type = FILE_OUT_SUR;
			//}
			i++;
		}
	}
}

int	is_redir_op(int i)
{
	return (i == FILE_IN
		|| i == HERE_DOC
		|| i == FILE_OUT
		|| i == FILE_OUT_SUR);
}

int	redir_op_to_file_type(int i)
{
	return ((i == FILE_IN) * OPEN_FILE
		+ (i == HERE_DOC) * LIMITOR
		+ (i == FILE_OUT) * EXIT_FILE
		+ (i == FILE_OUT_SUR) * EXIT_FILE_A);
}
