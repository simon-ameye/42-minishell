/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 16:58:44 by sameye            #+#    #+#             */
/*   Updated: 2021/12/18 18:11:53 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_word(t_token *tokens, char *line, int start, int len)
{
	int	index;

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

int	get_words(t_token *tokens, char *line, t_word word)
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
			break ;
		}
		else
			word.len++;
	}
	return (EXIT_SUCCESS);
}
