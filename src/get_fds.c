/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:36:49 by sameye            #+#    #+#             */
/*   Updated: 2021/12/19 20:51:07 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;

static void	print_ambiguous_redirect(char*s)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
}

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

static int	is_file(int i)
{
	return (i == OPEN_FILE
		|| i == LIMITOR
		|| i == EXIT_FILE
		|| i == EXIT_FILE_A);
}

int	get_fds(t_proc *proc, t_proc *procs, char *line)
{
	int	i;

	i = 0;
	while (proc->tokens[i].word)
	{
		if (is_file(proc->tokens[i].type) && proc->tokens[i].word[0] == '\0')
		{
			print_ambiguous_redirect(proc->tokens[i].expanded);
			return (EXIT_FAILURE);
		}
		if (proc->tokens[i].type == EXIT_FILE
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
