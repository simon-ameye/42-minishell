/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:36:49 by sameye            #+#    #+#             */
/*   Updated: 2022/01/03 14:50:18 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;

static int	get_proc_fdin(int *fd, char *filename)
{
	if (fd)
	{
		if (*fd != -1)
			close(*fd);
		*fd = open(filename, O_RDONLY, 0644);
		if (*fd == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(filename, STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			g_exitval = 1;
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static int	get_proc_fdout(int *fd, char *filename, t_token_type type)
{
	if (fd)
	{
		if (*fd != -1)
			close(*fd);
		if (type == EXIT_FILE)
			*fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
		else
			*fd = open(filename, O_CREAT | O_RDWR, 0644);
		if (*fd == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(filename, STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			g_exitval = 1;
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	is_file(int i)
{
	return (i == OPEN_FILE
		|| i == LIMITOR
		|| i == EXIT_FILE
		|| i == EXIT_FILE_A);
}

int	check_fd(t_token token)
{
	if (token.type == AMBIGOUS_REDIRECT)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(token.expanded, STDERR_FILENO);
		ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else if (is_file(token.type) && token.word[0] == '\0')
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(token.word, STDERR_FILENO);
		ft_putstr_fd(": no such file or directory\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	get_fds(t_proc *proc, t_proc *procs, char *line)
{
	int	i;

	i = 0;
	while (proc->tokens[i].word)
	{
		if (check_fd(proc->tokens[i]))
			return (EXIT_FAILURE);
		else if (proc->tokens[i].type == EXIT_FILE
			&& get_proc_fdout(&proc->fdout, proc->tokens[i].word, EXIT_FILE))
			return (EXIT_FAILURE);
		else if (proc->tokens[i].type == EXIT_FILE_A
			&& get_proc_fdout(&proc->fdout, proc->tokens[i].word, EXIT_FILE_A))
			return (EXIT_FAILURE);
		else if (proc->tokens[i].type == OPEN_FILE
			&& get_proc_fdin(&proc->fdin, proc->tokens[i].word))
			return (EXIT_FAILURE);
		else if (proc->tokens[i].type == LIMITOR
			&& get_proc_here_doc(&proc->fdin, proc->tokens[i], procs, line))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
