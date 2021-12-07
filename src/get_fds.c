/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:36:49 by sameye            #+#    #+#             */
/*   Updated: 2021/12/07 17:47:52 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_proc_fdin(int *fd, char *filename)
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
		{
		// exit here
		// in case of echo < file1 < file2,
		// where both input files don't exist)
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(filename, STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static int	get_proc_fdout(int *fd, char *filename, t_token_type type)
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
		{
			//perror("minishell");
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(filename, STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	get_fds(t_proc *proc)
{
	int	i;
	int	err;

	// are these protections very useful ? ...
	err = 0;
	if (proc)
	{
		// same here
		if (proc->tokens)
		{
			i = 0;
			while (proc->tokens[i].word)
			{
				// 'AMBIGOUS_REDIRECT'
				if (proc->tokens[i].type == AMBIGOUS_REDIRECT)
				{
					ft_putstr_fd("ambiguous redirect\n", STDERR_FILENO);
					err += 1;
				}
				// '>'
				if (proc->tokens[i].type == EXIT_FILE)
					err += get_proc_fdout(&proc->fdout, proc->tokens[i].word, EXIT_FILE);
				// '>>'
				else if (proc->tokens[i].type == EXIT_FILE_RET)
					err += get_proc_fdout(&proc->fdout, proc->tokens[i].word, EXIT_FILE_RET);
				// '<'
				else if (proc->tokens[i].type == OPEN_FILE)
					err += get_proc_fdin(&proc->fdin, proc->tokens[i].word);
				// '<<'
				else if (proc->tokens[i].type == LIMITOR)
					err += get_proc_here_doc(&proc->fdin, proc->tokens[i], *proc->env);
				if (err)
				{
					proc->ftype = NO_FUNCTION;
					return (EXIT_SUCCESS);
				}
				i++;
			}
		}
	}
	return (EXIT_SUCCESS);
}
