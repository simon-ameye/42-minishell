/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 13:31:07 by sameye            #+#    #+#             */
/*   Updated: 2021/12/18 14:20:44 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;

static void	do_pipes(t_proc *procs)
{
	int	pipefd[2];
	int	i;

	procs[0].stream_in = dup(STDIN_FILENO);
	i = 1;
	while (!procs[i].is_last)
	{
		if (pipe(pipefd) == -1)
		{
			free(procs);
			exit(EXIT_FAILURE);
		}
		procs[i].stream_in = pipefd[0];
		procs[i - 1].stream_out = pipefd[1];
		procs[i].prev_stream_out = pipefd[1];
		procs[i - 1].next_stream_in = pipefd[0];
		i++;
	}
	procs[i - 1].stream_out = dup(STDOUT_FILENO);
}

static void	do_redirs(t_proc *procs)
{
	int	i;

	i = 0;
	while (!procs[i].is_last)
	{
		if (procs[i].fdout > 0)
		{
			secure_close(procs[i].stream_out);
			procs[i].stream_out = procs[i].fdout;
			procs[i].fdout = -1;
		}
		if (procs[i].fdin > 0)
		{
			secure_close(procs[i].stream_in);
			procs[i].stream_in = procs[i].fdin;
			procs[i].fdin = -1;
		}
		i++;
	}
}

static void	do_forks(t_proc *procs)
{
	int	i;

	i = 0;
	while (!procs[i].is_last)
	{
		procs[i].pid = fork();
		if (procs[i].pid == -1)
		{
			free_procs(procs);
			exit(EXIT_FAILURE);
		}
		if (procs[i].pid == 0)
		{
			if (!(procs[i].ftype == NO_FUNCTION || procs[i].ftype == EXIT))
				g_exitval = 0;
			close_all_streams_except_current(procs, i);
			exec_child(&procs[i], procs);
			free_env(procs->env);
			free_procs(procs);
			close_std_streams();
			exit(g_exitval);
		}
		secure_close(procs[i].stream_in);
		secure_close(procs[i].stream_out);
		i++;
	}
}

static void	do_waits(t_proc *procs)
{
	int	i;
	int	wstatus;

	i = 0;
	while (!procs[i].is_last)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		if (waitpid(procs[i].pid, &wstatus, 0) == -1)
			perror(NULL);
		if (WIFEXITED(wstatus))
			g_exitval = WEXITSTATUS(wstatus);
		if (WIFSIGNALED(wstatus))
		{
			if (i == 0)
				ft_putstr_fd("\n", STDERR_FILENO);
			g_exitval = WTERMSIG(wstatus) + 128;
		}
		i++;
	}
}

void	exec(t_proc *procs)
{
	if (procs)
	{
		if (procs[0].ftype == EXECVE
			|| (!procs[0].is_last && !procs[1].is_last))
		{
			do_pipes(procs);
			do_redirs(procs);
			do_forks(procs);
			do_waits(procs);
			init_signals();
		}
		else
		{
			procs[0].stream_in = dup(STDIN_FILENO);
			procs[0].stream_out = dup(STDOUT_FILENO);
			do_redirs(procs);
			exec_child(&procs[0], procs);
		}
		free_procs(procs);
	}
}
