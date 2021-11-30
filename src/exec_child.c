#include "minishell.h"

static void	run_execve(t_proc *proc)
{
	int		i;
	int		len;
	char	**arg;

	len = 0;
	while (proc->tokens[len].word)
		len++;

	arg = malloc(sizeof(char *) * (len + 1));
	if (!arg)
		exit(222); // tmp

	i = 0;
	while (proc->tokens[i].word)
	{
		if (proc->tokens[i].type == WORD
		|| proc->tokens[i].type == FUNCTION) // ?
			 arg[i] = proc->tokens[i].word;
		i++;
	}
	arg[i] = NULL;
	if (proc->path)
	{
		if (execve(proc->path, arg, proc->env) == -1)
			perror("Error");
	}
	free(arg);
}

static void	exec_proc(t_proc *proc, t_proc *procs)
{
	if (proc)
	{
		// add all builtins
		if (proc->ftype == ENV)
			builtin_env(proc->env);
		else if (proc->ftype == EXIT)
			builtin_exit(proc, procs);
		else if (proc->ftype == ECHO)
			builtin_echo(proc);
		else
		{
			run_execve(proc);
		}
	}
}

static void	redirect_io(t_proc *proc)
{
	// output
	if (proc->fdout != -1)
	{
		dup2(proc->fdout, STDOUT_FILENO);
		close(proc->fdout);
	//	close(proc->stream_out);
		proc->stream_out = proc->fdout;
	}
	else if (proc->stream_out != STDOUT_FILENO)
	{
		dup2(proc->stream_out, STDOUT_FILENO);
		close(proc->stream_out);
	}
	// input
	if (proc->fdin != -1)
	{
		dup2(proc->fdin, STDIN_FILENO);
		close(proc->fdin);
	//	close(proc->stream_in);
		proc->stream_in = proc->fdin;
	}
	else if (proc->stream_in != STDIN_FILENO)
	{
		dup2(proc->stream_in, STDIN_FILENO);
		close(proc->stream_in);
	}
}

static void	save_stream_status(int *saved_std)
{
	saved_std[0] = dup(STDIN_FILENO);
	saved_std[1] = dup(STDOUT_FILENO);
}

static void	restore_stream_status(int *saved_std)
{
	dup2(saved_std[0], STDIN_FILENO);
	dup2(saved_std[1], STDOUT_FILENO);
	close(saved_std[0]);
	close(saved_std[1]);
}

void	exec_child(t_proc *proc, t_proc *procs)
{
	int saved_std[2];

	save_stream_status(saved_std);
	redirect_io(proc);
	exec_proc(proc, procs);
	free_procs(procs);
	restore_stream_status(saved_std);
}
