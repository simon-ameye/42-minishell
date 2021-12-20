/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <trobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 20:33:15 by trobin            #+#    #+#             */
/*   Updated: 2021/12/20 20:33:17 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*hd_quotes_expand_str(char *s, char **env,
	int force_expand, int quote_keep)
{
	char	*res;
	char	quote;
	int		quotes_spotted;

	if (init_res(&res, s))
		return (NULL);
	quote = 0;
	quotes_spotted = 0;
	while (*s)
	{
		if (switch_quote(&quote, *s) && !quote_keep)
			threat_silent_quote(&s, &quotes_spotted);
		else if (*s == '$' && (quote != '\'' || force_expand))
			dollar_expand(&res, &s, env);
		else
			add_char(res, &s);
		if (!res)
			return (NULL);
	}
	return (res);
}

char	*remove_quotes_str(char *str)
{
	int		i;
	char	*res;
	char	quote;

	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (res == NULL)
		return (NULL);
	quote = 0;
	i = 0;
	while (*str)
	{
		if (*str != '"' && *str != '\'')
			res[i++] = *str;
		else if (!quote)
			quote = *str;
		else if (*str == quote)
			quote = 0;
		else if (*str != quote)
			res[i++] = *str;
		str++;
	}
	res[i] = '\0';
	return (res);
}
