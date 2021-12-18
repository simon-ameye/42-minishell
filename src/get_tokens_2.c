/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 16:58:48 by sameye            #+#    #+#             */
/*   Updated: 2021/12/18 17:12:32 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int tokens_nb(t_token *tokens)
{
	int i;

	i = 0;
	while (tokens[i].word)
		i++;
	return (i);
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
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

void	get_quote_operator_separator(char *line, t_word *word)
{
	switch_quote(&(word->quote), line[word->start + word->len]);
	word->op_len = operator_len(line + word->start + word->len);
	word->sp_len = separator_len(line + word->start + word->len);
}
