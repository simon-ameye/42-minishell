/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_and_expand.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 13:49:53 by sameye            #+#    #+#             */
/*   Updated: 2021/12/20 22:34:54 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_char(char *res, char **word)
{
	res[ft_strlen(res)] = **word;
	*word += 1;
}

int	init_res(char **res, char *word)
{
	int		word_len;

	word_len = ft_strlen(word);
	*res = malloc(sizeof(char) * (word_len + 1));
	if (*res == NULL)
		return (EXIT_FAILURE);
	ft_bzero(*res, word_len + 1);
	return (EXIT_SUCCESS);
}

void	threat_silent_quote(char **word, int *quotes_spotted)
{
	*quotes_spotted = 1;
	*word += 1;
}

char	*quotes_expand_str(char *word, char **env,
	int keep_quotes_force_expands, int *type)
{
	char	*res;
	char	quote;
	int		quotes_spotted;

	if (init_res(&res, word))
		return (NULL);
	quote = 0;
	quotes_spotted = 0;
	while (*word)
	{
		if (switch_quote(&quote, *word) && !keep_quotes_force_expands)
			threat_silent_quote(&word, &quotes_spotted);
		else if (*word == '$'
			&& (quote != '\'' || keep_quotes_force_expands))
			dollar_expand(&res, &word, env);
		else
			add_char(res, &word);
		if (!res)
			return (NULL);
	}
	if (type && !ft_strlen(res) && !quotes_spotted)
		*type = IGNORED;
	return (res);
}

int	remove_quotes_and_expand(t_proc proc)
{
	int		i;
	char	*tmp;

	if (proc.tokens)
	{
		i = 0;
		while (proc.tokens[i].word)
		{
			if (proc.tokens[i].type != LIMITOR)
			{
				tmp = quotes_expand_str(proc.tokens[i].word,
						*proc.env, 0, &proc.tokens[i].type);
				if (!tmp)
					return (EXIT_FAILURE);
				if (ft_strcmp(tmp, proc.tokens[i].word)
					&& ft_strncmp(proc.tokens[i].word, "\"$\"", 3))
					proc.tokens[i].expanded = proc.tokens[i].word;
				else
					free(proc.tokens[i].word);
				proc.tokens[i].word = tmp;
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
