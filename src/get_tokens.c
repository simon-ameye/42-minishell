/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:08:48 by sameye            #+#    #+#             */
/*   Updated: 2021/12/10 00:37:30 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_tokens(t_token *tokens, int len)
{
	int i;

	i = 0;
	while (i <= len - 1)
	{
		tokens[i].word = NULL;
		tokens[i].type = WORD;
		tokens[i].expanded = 0;
		i++;
	}
}

static int	tokens_nb(t_token *tokens)
{
	int i;

	i = 0;
	while (tokens[i].word)
		i++;
	return (i);
}

static int	add_word(t_token *tokens, char *line, int start, int len)
{
	int index;

	if (!len)
		return (EXIT_SUCCESS);
	index = tokens_nb(tokens);
	tokens[index].word = malloc(sizeof(char) * (len + 1));
	if (!tokens[index].word)
		return (EXIT_FAILURE);
	ft_strncpy(tokens[index].word, line + start, len);
	tokens[index].word[len] = '\0';
	return (EXIT_SUCCESS);
}

static int	operator_len(char *line)
{
	if (line[0])
	{
		if (ft_strncmp(line, ">>", 2) == 0)
			return (2);
		if (ft_strncmp(line, "<<", 2) == 0)
			return (2);
	}
	if (ft_strncmp(line, ">", 1) == 0)
		return (1);
	if (ft_strncmp(line, "<", 1) == 0)
		return (1);
	return (0);
}

static int	separator_len(char *line)
{
	int i;

	i = 0;
	while (line[i] && ft_isblank(line[i]))
		i++;
	return (i);
}

static char	switch_quote(char quote, char c)
{
	if (c == '"' || c == '\'')
	{
		if (!quote)
			return (c);
		else if (c == quote)
			return (0);
	}
	return (quote);
}

static int	get_words(t_token *tokens, char *line)
{
	int		len;
	int		start;
	int		op_len;
	int		sp_len;
	char	quote;

	start = 0;
	len = 0;
	quote = 0;
	while (1)
	{
		quote = switch_quote(quote, line[start + len]);
		op_len = operator_len(line + start + len);
		sp_len = separator_len(line + start + len);
		//one or more separators are found outside quotes:
		//	we create a new word with all chars since last separator
		if (!quote && sp_len) 
		{
			if (add_word(tokens, line, start, len))
				return (EXIT_FAILURE);
			start = start + len + sp_len;
			len = 0;
		}
		//one operator is found outside quotes:
		//	we create a new word with all chars since last separator
		//	we also add a word with the operator
		else if (!quote && op_len)
		{
			if (add_word(tokens, line, start, len))
				return (EXIT_FAILURE);
			if (add_word(tokens, line, start + len, op_len))
				return (EXIT_FAILURE);
			start = start + len + op_len;
			len = 0;
		}
		//end of line :
		//	we create a new word
		else if (!line[start + len])
		{
			if (add_word(tokens, line, start, len))
				return (EXIT_FAILURE);
			break ;
		}
		//nothing special :
		//	we increase len to add char to current word
		else
			len++;
	}
	return (EXIT_SUCCESS);
}

void	get_tokens(t_proc *procs)
{
	int		i;

	if (procs)
	{
		i = 0;
		while (!procs[i].is_last)
		{
			procs[i].tokens = malloc(sizeof(t_token) * (ft_strlen(procs[i].str) + 1));
			if (!procs[i].tokens)
			{
				free_procs(procs);
				exit(EXIT_FAILURE);
			}
			init_tokens(procs[i].tokens, ft_strlen(procs[i].str) + 1);
			if (get_words(procs[i].tokens, procs[i].str))
			{
				free_procs(procs);
				exit(EXIT_FAILURE);
			}
			i++;
		}
	}
}
