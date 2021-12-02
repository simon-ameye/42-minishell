#include "minishell.h"

extern unsigned char	g_exitval;

static void	create_childs(t_proc *procs)
{
	int	i;
	int	code;

	// - at least two process
	// OR
	// - one one execve process
	if ((procs && !procs[0].is_last && !procs[1].is_last)
	|| (procs && procs[0].ftype == EXECVE))
	{
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
				exec_child(&procs[i], procs);
				printf("Error: child return\n"); // tmp
				exit(4242); //tmp
			}
			if (i > 0)
				close(procs[i].stream_in);
			if (!procs[i + 1].is_last)
				close(procs[i].stream_out);
			i++;
		}
		i = 0;
		while (!procs[i].is_last)
		{
			waitpid(procs[i].pid, &code, 0);
			if (code)
				g_exitval = WEXITSTATUS(code);
			i++;
		}
		free_procs(procs); //valgrind fix
	}
	// one process bultin
	else
	{
		// we are in parent process
		exec_child(&procs[0], procs);
	}
}

static void	create_pipes(t_proc *procs)
{
	int	pipefd[2];
	int	i;

	// we need at least 2 process
	if (procs && !procs[0].is_last && !procs[1].is_last)
	{
		procs[0].stream_in = STDIN_FILENO;
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
			i++;
		}
		procs[i - 1].stream_out = STDOUT_FILENO;
	}
	else
	{
		procs[0].stream_in = STDIN_FILENO;
		procs[0].stream_out = STDOUT_FILENO;
	}
}

void	exec(t_proc *procs)
{
	if (procs)
	{
		// do not forget to close fd
		// streams are automatically closed by execve
		create_pipes(procs);
		create_childs(procs);
	}
}
