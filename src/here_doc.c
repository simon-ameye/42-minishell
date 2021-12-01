#include "minishell.h"

void	get_proc_here_doc(int *fd, char *eof)
{
	char		*line;
	const char	*filename;
	
	filename = "minish-thd42";
	*fd = open(filename, O_CREAT | O_APPEND | O_RDWR, 0644);
	if (*fd == -1)
	{
		unlink(filename);
		perror("minishell: heredoc:");
		return ;
	}
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, eof))
			break ;
		ft_putstr_fd(line, *fd);
		ft_putstr_fd("\n", *fd);
	}
	close(*fd);
	*fd = open(filename, O_RDONLY, 0644);
	unlink(filename);
}
