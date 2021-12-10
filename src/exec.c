#include "minishell.h"

extern unsigned char	g_exitval;

static void	do_pipes(t_proc *procs)
{
	int	pipefd[2];
	int	i;

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
		procs[i].prev_stream_out =  pipefd[1];
		procs[i - 1].next_stream_in = pipefd[0];
		i++;
	}
	procs[i - 1].stream_out = STDOUT_FILENO;
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
			close(procs[i].prev_stream_out);
			close(procs[i].next_stream_in);
			exec_child(&procs[i], procs);
			exit(g_exitval);
		}
		if (i > 0)
			close(procs[i].stream_in);
		if (!procs[i + 1].is_last)
			close(procs[i].stream_out);
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
		// do not forget to close fd
		// streams are automatically closed by execve
		// cf. valgrind --track-fds=yes
		if (procs[0].ftype == EXECVE
		|| (!procs[0].is_last && !procs[1].is_last))
		{
			do_pipes(procs);
			do_forks(procs);
			do_waits(procs);
			init_signals();
			free_procs(procs);
		}
		else
		{
			procs[0].stream_in = STDIN_FILENO;
			procs[0].stream_out = STDOUT_FILENO;
			exec_child(&procs[0], procs);
		}
	}
}
