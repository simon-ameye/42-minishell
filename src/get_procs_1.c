/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_procs_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 19:33:46 by trobin            #+#    #+#             */
/*   Updated: 2021/12/18 14:25:59 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;

static int	syntax_error_pipe(char *line, int i)
{
	int	j;
	int	error;

	error = 0;
	if (i == 0)
		error = 1;
	j = i - 1;
	while (line[j] == ' ')
		j--;
	if (!line[j] || line[j] == '|' || line[j] == '<' || line[j] == '>')
		error = 1;
	j = i + 1;
	while (line[j] == ' ')
		j++;
	if (!line[j] || line[j] == '|' || line[j] == '<' || line[j] == '>')
		error = 1;
	if (error)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n",
			STDERR_FILENO);
		g_exitval = 2;
		return (1);
	}
	return (0);
}

static int	syntax_error_quote(char quote)
{
	if (quote == '\'')
		ft_putstr_fd("Error: simple quote not closed\n", STDERR_FILENO);
	else
		ft_putstr_fd("Error: double quote not closed\n", STDERR_FILENO);
	g_exitval = 2;
	return (0);
}

int	get_nb_procs(char *line)
{
	int		i;
	int		ret;
	char	quote;

	i = 0;
	ret = 1;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
			if (!line[i])
				return (syntax_error_quote(quote));
		}
		else if (line[i] == '|')
		{
			if (syntax_error_pipe(line, i))
				return (0);
			ret++;
		}
		i++;
	}
	return (ret);
}
