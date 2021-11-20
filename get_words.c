/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_words.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:08:48 by sameye            #+#    #+#             */
/*   Updated: 2021/11/20 16:28:48 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_str_words(char *str)
{
	int		dbq;
	int		sgq;
	int		len;
	char	**tab;
	int		i;
	int		j;
	int		inword;

	len = ft_strlen(str);
	tab = malloc(sizeof(char *) * (len + 1));
	sgq = 0;
	dbq = 0;
	inword = 0;

	i = -1;
	j = 0;
	while (*str)
	{
		if (ft_isblank(*str) && !sgq && !dbq)
		{
			if (inword == 1)
				inword = 0;
		}
		else if (*str == '"' && !sgq)
			dbq = 1 - dbq;
		else if (*str == '\'' && !dbq)
			sgq = 1 - sgq;
		else
		{
			if (inword)
			{
				tab[i] = join_char_free(tab[i], *str);
			}
			else if (!inword)
			{
				i++;
				j = 0;
				tab[i] = malloc(sizeof(char));
				tab[i][j] = '\0';
				tab[i] = join_char_free(tab[i], *str);
				inword = 1;
			}
		}
		str++;
	}
	i++;
	tab[i] = NULL;
	return (tab);
}

void	get_words(t_token **tokens)
{
	(void)tokens;
}

//  hsdhbsdhjcb 'axasx' "dwedw edd"