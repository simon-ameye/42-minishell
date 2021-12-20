/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 20:33:15 by trobin            #+#    #+#             */
/*   Updated: 2021/12/20 22:33:01 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
