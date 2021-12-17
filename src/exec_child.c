/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 13:26:28 by sameye            #+#    #+#             */
/*   Updated: 2021/12/17 13:26:29 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;

static void	exec_proc(t_proc *proc, t_proc *procs)
{
	if (proc)
	{
		if (proc->ftype == CD)
			builtin_cd(proc);
		if (proc->ftype == PWD)
			builtin_pwd();
		if (proc->ftype == ENV)
			builtin_env(*proc->env);
		else if (proc->ftype == EXIT)
			builtin_exit(proc, procs);
		else if (proc->ftype == ECHO)
			builtin_echo(proc);
		else if (proc->ftype == UNSET)
			builtin_unset(proc);
		else if (proc->ftype == EXPORT)
			builtin_export(proc);
		else
			run_execve(proc, procs);
	}
}

static void	redirect_io(t_proc *proc)
{
	dup2(proc->stream_in, STDIN_FILENO);
	secure_close(proc->stream_in);
	dup2(proc->stream_out, STDOUT_FILENO);
	secure_close(proc->stream_out);
}

static void	save_stream_status(t_proc *procs)
{
	procs->saved_std[0] = dup(STDIN_FILENO);
	procs->saved_std[1] = dup(STDOUT_FILENO);
}

static void	restore_stream_status(t_proc *procs)
{
	dup2(procs->saved_std[0], STDIN_FILENO);
	dup2(procs->saved_std[1], STDOUT_FILENO);
	close(procs->saved_std[0]);
	close(procs->saved_std[1]);
}

void	exec_child(t_proc *proc, t_proc *procs)
{
	save_stream_status(procs);
	redirect_io(proc);
	exec_proc(proc, procs);
	restore_stream_status(procs);
}
