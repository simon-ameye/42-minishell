/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 16:32:07 by trobin            #+#    #+#             */
/*   Updated: 2021/12/18 18:09:24 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	random_heredoc_name(char *filename)
{
	char	randomlist[10];
	int		fd;
	int		i;

	ft_strcpy(filename, "minish-thd42-");
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return ;
	read(fd, randomlist, 9);
	close(fd);
	i = 0;
	while (i <= 8)
	{
		randomlist[i] = (unsigned int)randomlist[i] % 10 + '0';
		i++;
	}
	randomlist[i] = '\0';
	ft_strcpy(filename + ft_strlen(filename), randomlist);
}

static	int	exit_heredoc(t_heredoc *hd, int *fd)
{
	if (!hd->line)
		write(1, "\n", 1);
	close(*fd);
	*fd = open(hd->filename, O_RDONLY);
	unlink(hd->filename);
	free(hd->delimiter);
	return (EXIT_SUCCESS);
}

static void	process_line(t_heredoc *hd, int *fd, t_proc *procs, char *ps1_line)
{
	char	*tmp;

	tmp = dollar_expand_str(hd->line, *procs->env, 1);
	if (!tmp)
	{
		free(ps1_line);
		exit_heredoc(hd, fd);
		exit_minishell(procs, procs->env);
	}
	ft_putstr_fd(tmp, *fd);
	ft_putstr_fd("\n", *fd);
	free(tmp);
}

static	int	init_heredoc(t_heredoc *hd, t_token token, int *fd)
{
	random_heredoc_name(hd->filename);
	*fd = open(hd->filename, O_CREAT | O_APPEND | O_RDWR, 0600);
	if (*fd == -1)
	{
		unlink(hd->filename);
		ft_putstr_fd("minishell: heredoc: ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(hd->filename, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	if (token.expanded)
		hd->delimiter = remove_quotes_str(token.expanded);
	else
		hd->delimiter = remove_quotes_str(token.word);
	if (!hd->delimiter)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_proc_here_doc(int *fd, t_token token, t_proc *procs, char *ps1_line)
{
	t_heredoc	hd;

	hd.delimiter = NULL;
	if (init_heredoc(&hd, token, fd) == EXIT_FAILURE)
	{
		free(ps1_line);
		exit_minishell(procs, procs->env);
	}
	while (1)
	{
		hd.line = NULL;
		hd.line = readline("> ");
		if (!hd.line || !ft_strcmp(hd.line, hd.delimiter))
			break ;
		if (ft_strchr(token.word, '\'') || ft_strchr(token.word, '"'))
		{
			ft_putstr_fd(hd.line, *fd);
			ft_putstr_fd("\n", *fd);
		}
		else
			process_line(&hd, fd, procs, ps1_line);
	}
	return (exit_heredoc(&hd, fd));
}
