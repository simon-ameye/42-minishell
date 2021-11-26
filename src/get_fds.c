/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:36:49 by sameye            #+#    #+#             */
/*   Updated: 2021/11/26 11:51:59 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int are_alnums(char *s)
{
	if (s)
	{
		while (*s)
		{
			if (!ft_isalnum(*s))
				return (0);
			s++;
		}
	}
	return (1);
}

//modifier !!: 
static void	check_redir_syntax(t_proc *procs)
{
	int		i;
	int		j;

	if (procs)
	{
		i = 0;
		while(!procs[i].is_last)
		{
			j = 0;
			while (procs[i].words[j])
			{
				if (!ft_strcmp(procs[i].words[j], ">"))
				{
					if (!are_alnums(procs[i].words[j + 1]))
					{
						ft_putstr_fd("syntax error near unexpected proc >\n", STDERR_FILENO);
						free_procs(procs);
						exit(42);
					}
				}
				j++;
			}
			i++;
		}
	}
}

static void	remove_two_words(char **words, int j)
{
	free(words[j]);
	free(words[j + 1]);
	while (words[j + 2])
	{
		words[j] = words[j + 2];
		j++;
	}
	words[j] = NULL;
}

void	old_get_fds(t_proc *procs)
{
	int		i;
	int		j;

	check_redir_syntax(procs);
	if (procs)
	{
		i = 0;
		while(!procs[i].is_last)
		{
			j = 0;
			while (procs[i].words)
			{
				if (!ft_strcmp(procs[i].words[j], ">"))
				{
					procs[i].fdout = open(procs[i].words[j + 1], O_CREAT | O_RDWR, 0644);
					if (procs[i].fdout == -1)
						perror("ERROR :");
					remove_two_words(procs[i].words, j);
				}
				i--;
			}
			i++;
		}
	}
}

/* ************************************************************************** */

/*
 *
 * RIP

// need substitution a la volee

char	*get_next_word(char *s)
{
	char	*word;

	word = NULL;
	if (s)
	{
		// skip blanks
		while (*s == ' ') // is_blank ?
			s++;
		// next word in within quotes
		if (*s == '\'' || *s == '"')
		{
			word = ft_strndup(s + 1, elem_index(s + 1, *s));
			break ;
		}
		// next word is outside of quotes
		if (*s)
		{
			int i = 0;
			while (!ft_isalnum(s[i]))
				s++;
			if (s[i])
				word = ft_strndup(s, i);
			else
				word = ft_strndup(s, ft_strlen(s));
			break ;
		}
	}
	return (word);
}

void	get_proc_input_filename(t_proc *proc)
{
	int		i;
	char	quote;

	if (proc)
	{
		i = 0;
		while (proc->str[i])
		{
			if (line[i] == '\'' || line[i] == '"')
			{
				quote = line[i++];
				while (line[i] && line[i] != quote)
					i++;
			}
			else if (proc->str[i] == '<')
			{
				proc->in.filename = get_next_word(&proc->str[i]);
				//proc->in.fd = open(proc->in.filename, O_RDONLY);
			}
			i++;
		}
	}
}

*/

/* ************************************************************************** */

static void	get_proc_fdin(int *fd, char *filename, t_token_type type)
{
	// are these protections very useful ? ...
	if (fd)
	{
		// if output fd already set, close it.
		if (*fd != -1)
			close(*fd);
		// '<'
		*fd = open(filename, O_RDONLY, 0644);
		// check for open() failure
		if (*fd == -1)
			perror("ERROR :");
	}
}

static void	get_proc_fdout(int *fd, char *filename, t_token_type type)
{
	// are these protections very useful ? ...
	if (fd)
	{
		// if output fd already set, close it.
		if (*fd != -1)
			close(*fd);
		// '>'
		if (type == EXIT_FILE)
			*fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
		// '>>'
		else
			*fd = open(filename, O_CREAT | O_RDWR, 0644);
		// check for open() failure
		if (*fd == -1)
			perror("ERROR :");
	}
}

void	get_fds(t_proc *proc)
{
	int	i;

	// are these protections very useful ? ...
	if (proc)
	{
		// same here
		if (proc->tokens)
		{
			i = 0;
			while (proc->tokens[i])
			{
				// '>'
				if (proc->tokens[i].type == EXIT_FILE)
				{
					get_proc_fdout(&proc->fdout, proc->tokens[i].word, EXIT_FILE);
				}
				// '>>'
				else if (proc->tokens[i].type == EXIT_FILE_RET)
				{
					get_proc_fdout(&proc->fdout, proc->tokens[i].word, EXIT_FILE_RET);
				}
				// '<'
				if (proc->tokens[i].type == OPEN_FILE)
				{
					get_proc_fdin(&proc->fdin, proc->tokens[i].word, EXIT_FILE_RET);
				}
				i++;
			}
		}
	}
}
