/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:08:48 by sameye            #+#    #+#             */
/*   Updated: 2021/12/16 15:56:36 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;

static void init_tokens(t_token *tokens, int len)
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

static int tokens_nb(t_token *tokens)
{
	int i;

	i = 0;
	while (tokens[i].word)
		i++;
	return (i);
}

static int add_word(t_token *tokens, char *line, int start, int len)
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

static int operator_len(char *line)
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

static int separator_len(char *line)
{
	int i;

	i = 0;
	while (line[i] && ft_isblank(line[i]))
		i++;
	return (i);
}

static int	separator_spotted(t_token *tokens, char *line, t_word *word)
{
	if (add_word(tokens, line, word->start, word->len))
		return (EXIT_FAILURE);
	word->start = word->start + word->len + word->sp_len;
	word->len = 0;
	return (EXIT_SUCCESS);
}

static int	operator_spotted(t_token *tokens, char *line, t_word *word)
{
	if (add_word(tokens, line, word->start, word->len))
		return (EXIT_FAILURE);
	if (add_word(tokens, line, word->start + word->len, word->op_len))
		return (EXIT_FAILURE);
	word->start = word->start + word->len + word->op_len;
	word->len = 0;
	return (EXIT_SUCCESS);
}

static void	get_quote_operator_separator(char *line, t_word *word)
{
	switch_quote(&(word->quote), line[word->start + word->len]);
	word->op_len = operator_len(line + word->start + word->len);
	word->sp_len = separator_len(line + word->start + word->len);
}

static void init_word(t_word *word)
{
	word->start = 0;
	word->len = 0;
	word->quote = 0;
}

static int get_words(t_token *tokens, char *line, t_word word)
{
	while (1)
	{
		get_quote_operator_separator(line, &word);
		if (!word.quote && word.sp_len)
		{
			if (separator_spotted(tokens, line, &word))
				return (EXIT_FAILURE);
		}
		else if (!word.quote && word.op_len)
		{
			if (operator_spotted(tokens, line, &word))
				return (EXIT_FAILURE);
		}
		else if (!line[word.start + word.len])
		{
			if (add_word(tokens, line, word.start, word.len))
				return (EXIT_FAILURE);
			break;
		}
		else
			word.len++;
	}
	return (EXIT_SUCCESS);
}

void get_tokens(t_proc *procs)
{
	int i;
	t_word word;

	if (procs)
	{
		i = 0;
		while (!procs[i].is_last)
		{
			procs[i].tokens = malloc(sizeof(t_token) * (ft_strlen(procs[i].str) + 1));
			if (!procs[i].tokens)
			{
			//	free_env(procs->env);
			//	free_procs(procs);
			//	exit(EXIT_FAILURE);
				ft_putstr_fd("minishell: error: malloc fail\n", STDERR_FILENO);
				g_exitval = EXIT_FAILURE;
				new_exit_minishell(procs, procs->env);
			}
			init_tokens(procs[i].tokens, ft_strlen(procs[i].str) + 1);
			init_word(&word);
			if (get_words(procs[i].tokens, procs[i].str, word))
			{
			//	free_env(procs->env);
			//	free_procs(procs);
			//	exit(EXIT_FAILURE);
				ft_putstr_fd("minishell: error: malloc fail\n", STDERR_FILENO);
				g_exitval = EXIT_FAILURE;
				new_exit_minishell(procs, procs->env);
			}
			i++;
		}
	}
}
