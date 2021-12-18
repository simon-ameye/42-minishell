/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_procs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 19:37:00 by trobin            #+#    #+#             */
/*   Updated: 2021/12/18 14:44:41 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_proc(t_proc *proc, char ***env)
{
	if (proc)
	{
		proc->str = NULL;
		proc->path = NULL;
		proc->tokens = NULL;
		proc->ftype = 0;
		proc->fdin = -1;
		proc->fdout = -1;
		proc->stream_in = -1;
		proc->stream_out = -1;
		proc->prev_stream_out = -1;
		proc->next_stream_in = -1;
		proc->is_last = 0;
		proc->env = env;
		proc->pid = -1;
		proc->saved_std[0] = -1;
		proc->saved_std[1] = -1;
	}
}

static void	go_to_next_quote(char *line, int *hi, char *quote)
{
	*quote = line[(*hi)++];
	while (line[(*hi)] && line[(*hi)] != *quote)
		(*hi)++;
}

static char	*get_proc_str(char *line, int proc_index)
{
	int		lo;
	int		hi;
	int		current_proc_index;
	char	quote;

	lo = 0;
	hi = 0;
	current_proc_index = -1;
	while (line[hi])
	{
		if (line[hi] == '\'' || line[hi] == '"')
			go_to_next_quote(line, &hi, &quote);
		else if (line[hi] == '|')
		{
			current_proc_index++;
			if (current_proc_index == proc_index)
				break ;
			else
				lo = hi + 1;
		}
		hi++;
	}
	return (ft_strndup(&line[lo], hi - lo));
}

static void	exit_get_procs(t_proc *procs, char ***env, char *line)
{
	ft_putstr_fd("minishell: error: malloc fail\n", STDERR_FILENO);
	free(line);
	exit_minishell(procs, env);
}

void	get_procs(t_proc **procs, char *line, char ***env)
{
	int	i;
	int	nb_procs;

	nb_procs = get_nb_procs(line);
	if (nb_procs)
	{
		*procs = malloc((sizeof(t_proc) * (nb_procs + 1)));
		if (!*procs)
			exit_get_procs(NULL, env, line);
		i = 0;
		while (i < nb_procs)
		{
			init_proc(&(*procs)[i], env);
			(*procs)[i].str = get_proc_str(line, i);
			if ((*procs)[i].str == NULL)
			{
				(*procs)[i + 1].is_last = 1;
				exit_get_procs(NULL, env, line);
			}
			i++;
		}
		(*procs)[nb_procs].is_last = 1;
	}
}
