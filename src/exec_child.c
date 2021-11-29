#include "minishell.h"

static void	run_execve(t_proc *proc)
{
	int	len;

	len = 0;
	while (proc->tokens[len].word)
		len++;

	char	**arg;
	arg = malloc(sizeof(char *) * (len + 1));
	if (!arg)
		exit(222); // tmp

	int	i;
	i = 0;

	while (proc->tokens[i].word)
	{
		if (proc->tokens[i].type == WORD
		|| proc->tokens[i].type == FUNCTION) // ?
		{
			 arg[i] = proc->tokens[i].word;
		}
		i++;
	}
	execve(proc->path, arg, proc->env);
}

static void	exec_proc(t_proc *proc)
{
	if (proc)
	{
		// add all builtins
		if (proc->ftype == EXIT)
			exit(4242);
		else
			run_execve(proc);
	}
}

static void	redirect_io(t_proc *proc)
{
	// tmp
	printf("child %d\n", proc->pid);
	// output
	if (proc->fdout != -1)
	{
		dup2(proc->fdout, STDOUT_FILENO);
		close(proc->stream_out);
		proc->stream_out = proc->fdout;
	}
	// ?
	else if (proc->stream_out != STDOUT_FILENO)
		dup2(proc->stream_out, STDOUT_FILENO);
	// input
	if (proc->fdin != -1)
	{
		dup2(proc->fdin, STDIN_FILENO);
		close(proc->stream_in);
		proc->stream_in = proc->fdin;
	}
	// ?
	else if (proc->stream_in != STDIN_FILENO)
		dup2(proc->stream_in, STDIN_FILENO);
	// tmp
	exit (56);
}

void	exec_child(t_proc *proc, t_proc *procs)
{
	redirect_io(proc);
	exec_proc(proc);
	free_procs(procs);
}

