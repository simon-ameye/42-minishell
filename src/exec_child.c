#include "minishell.h"

extern unsigned char	g_exitval;

static void	run_execve(t_proc *proc, t_proc *procs)
{
	int		i;
	int		j;
	char	**arg;

	i = 0;
	while (proc->tokens[i].word)
		i++;
	arg = malloc(sizeof(char *) * (i + 1));
	if (!arg)
		exit_minishell(procs, procs->env);
	i = 0;
	j = 0;
	while (proc->tokens[i].word)
	{
		if (proc->tokens[i].type == WORD
		|| proc->tokens[i].type == FUNCTION)
			 arg[j++] = proc->tokens[i].word;
		i++;
	}
	arg[j] = NULL;
	if (proc->path && execve(proc->path, arg, *proc->env) == -1)
		perror("minishell");
	free(arg);
}

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
