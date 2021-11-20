/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_words.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:08:48 by sameye            #+#    #+#             */
/*   Updated: 2021/11/20 13:07:31 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_str_words(char *str)
{
	int		sgquote;
	int		dbquote;
	int		len;
	char	**tab;
	int		i;
	int		inword;

	len = ft_strlen(str);
	tab = malloc(sizeof(char *) * (len + 1));
	sgquote = 0;
	dbquote = 0;
	inword = 0;

	str[i] = malloc(sizeof(char));
	while (str[i])
	{
		if (ft_isblank(str[i]) && sgquote == 0 && dbquote == 0)
		{
			if (inword == 1)
				inword = 0;
			i++;
		}
		else if (str[i] == '"' && sgquote == 0)
		{
			dbquote = 1 - dbquote;
			i++;
		}
		else if (str[i] == '\'' && dbquote == 0)
		{
			sgquote = 1 - sgquote;
			i++;
		}
		else
		{
			inword = 1 - inword;

		}
	}


	join_char_free()
	

}

void	get_words(t_token **tokens)
{
	char **tab;
	int i;

	tab = get_str_words("  echo blabla 'yooo sdsf' \"echo lool\"");
	i = 0;
	while(tab[i])
	{
		printf(tab[i]);
	}
}

//  hsdhbsdhjcb 'axasx' "dwedw edd"