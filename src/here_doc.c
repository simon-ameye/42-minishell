#include "minishell.h"

/*
 * todo : gestion des erreurs
 */

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

static char	*get_delimiter(t_token token)
{
	if (token.expanded)
		return (remove_quotes_str(token.expanded));
	else
		return (remove_quotes_str(token.word));
}

static int	heredoc_open_error(char *filename)
{
	unlink(filename);
	ft_putstr_fd("minishell: heredoc: ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

static	int	exit_heredoc(int *fd, char *filename, char *delimiter)
{
	close(*fd);
	*fd = open(filename, O_RDONLY);
	unlink(filename);
	free(filename);
	free(delimiter);
	return (EXIT_SUCCESS);
}

static	int	init_heredoc(int *fd, t_token token, char **filename, char **delimiter)
{
	*filename = random_heredoc_name();
	if (!*filename)
		return (EXIT_FAILURE);
	*fd = open(*filename, O_CREAT | O_APPEND | O_RDWR, 0600);
	if (*fd == -1)
		return (heredoc_open_error(*filename));
	*delimiter = get_delimiter(token);
	return (EXIT_SUCCESS);
}

int	get_proc_here_doc(int *fd, t_token token, char **env)
{
	char	*tmp;
	char	*line;
	char	*filename;
	char	*delimiter;
	
	init_heredoc(fd, token, &filename, &delimiter);
//	printf("word: %s\n", token.word);
//	printf("expanded: %s\n", token.expanded);
//	printf("delimiter: %s\n", delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
			break ;
		if (ft_strchr(token.word, '\'') || ft_strchr(token.word, '"'))
		{
			ft_putstr_fd(line, *fd);
			ft_putstr_fd("\n", *fd);
		}
		else
		{
			tmp = dollar_expand_str_heredoc(line, env);
			ft_putstr_fd(tmp, *fd);
			ft_putstr_fd("\n", *fd);
			free(tmp);
		}
	}
	return (exit_heredoc(fd, filename, delimiter));
}
