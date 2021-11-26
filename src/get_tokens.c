/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:08:48 by sameye            #+#    #+#             */
/*   Updated: 2021/11/26 19:16:42 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token *free_tokens_tab(t_token *tokens)
{
	free_tokens(tokens);
	return (NULL);
}

static void	init_tokens(t_token *tokens, int len)
{
	int i;

	i = 0;
	while (i <= len - 1)
	{
		tokens[i].word = NULL;
		tokens[i].type = 0;
		i++;
	}
}

static t_token	*get_proc_tokens(char *str)
{
	int		dbq;
	int		sgq;
	t_token	*tokens;
	int		i;
	int		inword;

	if (!str)
		return (NULL);
	tokens = malloc(sizeof(t_token) * (ft_strlen(str) + 1));
	if (!tokens)
		return (NULL);
	init_tokens(tokens, ft_strlen(str) + 1);
	sgq = 0;
	dbq = 0;
	inword = 0;
	i = -1;
	while (*str)
	{
		if (ft_isblank(*str) && !sgq && !dbq) //skip a character, eventually leave a word
			inword = 0;
		else if (!sgq && !dbq && (*str == '>' || *str == '<')) //if bracket, split words
		{
			i++;
			tokens[i].word = malloc(sizeof(char) * 3);
			if (tokens[i].word == NULL)
				return (free_tokens_tab(tokens));
			tokens[i].word[0] = *str;
			tokens[i].word[1] = '\0';
			if (*str == *(str + 1)) //double bracket
			{
				str++;
				tokens[i].word[1] = *str;
				tokens[i].word[2] = '\0';
			}
			inword = 0;
		}
		else //a characher will be appened to result
		{
			if (*str == '"' && !sgq)
				dbq = 1 - dbq;
			if (*str == '\'' && !dbq)
				sgq = 1 - sgq;
			if (!inword)
			{
				i++;
				tokens[i].word = malloc(sizeof(char));
				if (tokens[i].word == NULL)
					return (free_tokens_tab(tokens));
				tokens[i].word[0] = '\0';
				inword = 1;
			}
			tokens[i].word = join_char_free(tokens[i].word, *str);
			if (tokens[i].word == NULL)
				return (free_tokens_tab(tokens));
		}
		str++;
	}
	return (tokens);
}

void	get_tokens(t_proc *procs)
{
	int		i;

	if (procs)
	{
		i = 0;
		while (!procs[i].is_last)
		{
			procs[i].tokens = get_proc_tokens(procs[i].str);
			if (!procs[i].tokens)
			{
				free_procs(procs);
				exit(EXIT_FAILURE);
			}
			i++;
		}
	}
}
