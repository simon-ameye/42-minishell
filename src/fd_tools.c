#include "minishell.h"

void secure_close(int fd)
{
	if (fd >= 0)
		close(fd);
}

void close_saved_fd_and_streams(t_proc *procs)
{
	if (procs)
	{
		secure_close(procs->saved_std[0]);
		secure_close(procs->saved_std[1]);
		secure_close(0);
		secure_close(1);
	}
}

void close_all_streams_except_current(t_proc *procs, int i)
{
	int k;

	k = 0;
	while (!procs[k].is_last)
	{
		if (k != i)
		{
			secure_close(procs[k].stream_out);
			secure_close(procs[k].stream_in);
		}
		k++;
	}
}
