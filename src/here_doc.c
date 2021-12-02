#include "minishell.h"

static char *random_heredoc_name(void)
{
	char	randomlist[10];
	int		fd;
	int		i;

	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (NULL);
	read(fd, randomlist, 9);
	close(fd);
	i = 0;
	while (i <= 8)
	{
		randomlist[i] = (unsigned int)randomlist[i] % 10 + '0';
		i++;
	}
	randomlist[i] = '\0';
	return (ft_strjoin("minish-thd42-", randomlist));
}

int	get_proc_here_doc(int *fd, char *eof)
{
	char	*line;
	char	*filename;
	
	filename = random_heredoc_name();
	if (!filename)
		return (EXIT_FAILURE);
	*fd = open(filename, O_CREAT | O_APPEND | O_RDWR, 0600);
	if (*fd == -1)
	{
		unlink(filename);
		ft_putstr_fd("minishell: heredoc: ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (EXIT_FAILURE);
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
	*fd = open(filename, O_RDONLY);
	unlink(filename);
	free(filename);
	return (EXIT_SUCCESS);
}
