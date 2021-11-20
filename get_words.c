/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_words.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:08:48 by sameye            #+#    #+#             */
/*   Updated: 2021/11/20 17:31:07 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_str_words(char *str)
{
	int		dbq;
	int		sgq;
	char	**tab;
	int		i;
	int		inword;

	if (!str)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_strlen(str) + 1));
	sgq = 0;
	dbq = 0;
	inword = 0;

	i = -1;
	while (*str)
	{
		if (ft_isblank(*str) && !sgq && !dbq)
		{
			if (inword)
				inword = 0;
		}
		else if (*str == '"' && !sgq)
			dbq = 1 - dbq;
		else if (*str == '\'' && !dbq)
			sgq = 1 - sgq;
		else
		{
			if (!inword)
			{
				i++;
				tab[i] = malloc(sizeof(char));
				tab[i][0] = '\0';
				inword = 1;
			}
			tab[i] = join_char_free(tab[i], *str);
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