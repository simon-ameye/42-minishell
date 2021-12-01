/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:36:49 by sameye            #+#    #+#             */
/*   Updated: 2021/12/01 18:37:11 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_proc_fdin(int *fd, char *filename)
{
	// are these protections very useful ? ...
	if (fd)
	{
		// if output fd already set, close it.
		if (*fd != -1)
			close(*fd);
		// '<'
		*fd = open(filename, O_RDONLY, 0644);
		// check for open() failure
		if (*fd == -1)
		// exit here
		// in case of echo < file1 < file2,
		// where both input files don't exist)
			perror("ERROR :");
	}
}

static void	get_proc_fdout(int *fd, char *filename, t_token_type type)
{
	// are these protections very useful ? ...
	if (fd)
	{
		// if output fd already set, close it.
		if (*fd != -1)
			close(*fd);
		// '>'
		if (type == EXIT_FILE)
			*fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
		// '>>'
		else
			*fd = open(filename, O_CREAT | O_RDWR, 0644);
		// check for open() failure
		if (*fd == -1)
			perror("ERROR :");
	}
}

int	get_fds(t_proc *proc)
{
	int	i;

	// are these protections very useful ? ...
	if (proc)
	{
		// same here
		if (proc->tokens)
		{
			i = 0;
			while (proc->tokens[i].word)
			{
				// '>'
				if (proc->tokens[i].type == EXIT_FILE)
				{
					get_proc_fdout(&proc->fdout, proc->tokens[i].word, EXIT_FILE);
				}
				// '>>'
				else if (proc->tokens[i].type == EXIT_FILE_RET)
				{
					get_proc_fdout(&proc->fdout, proc->tokens[i].word, EXIT_FILE_RET);
				}
				// '<'
				else if (proc->tokens[i].type == OPEN_FILE)
				{
					get_proc_fdin(&proc->fdin, proc->tokens[i].word);
				}
				// '<<'
				else if (proc->tokens[i].type == LIMITOR)
				{
					get_proc_here_doc(&proc->fdin, proc->tokens[i].word);
				}
				i++;
			}
		}
	}
	return (EXIT_SUCCESS);
}
