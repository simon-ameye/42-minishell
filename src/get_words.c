/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_words.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:08:48 by sameye            #+#    #+#             */
/*   Updated: 2021/11/21 19:05:31 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_words(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

/*
IMPOSSIBLE DE RACCOURCIR LA FONCTION PROPREMENT !!
char	**get_words_char(int *i, char **tab, int *inword, char c)
{
	if (!*inword)
	{
		(*i)++;
		tab[*i] = malloc(sizeof(char));
		if(!tab[*i])
		{
			freetab(tab);
			return (NULL);
		}
		tab[*i][0] = '\0';
		*inword = 1;
	}
	tab[*i] = join_char_free(tab[*i], c);
	if(!tab[*i])
	{
		freetab(tab);
		return (NULL);
	}
	return (tab);
}

char	**get_words_iter(int *i, char **tab, char c, int *sgq, int *dbq, int *inword)
{
	if (ft_isblank(c) && !*sgq && !*dbq)
	{
		if (*inword)
			*inword = 0;
	}
	else if (c == '"' && !*sgq)
		*dbq = 1 - *dbq;
	else if (c == '\'' && !*dbq)
		*sgq = 1 - *sgq;
	else
	{
		tab = get_words_char(i, tab, inword, c);
		if (!tab)
			return (NULL);
	}
	return (tab);
}

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
	if (!tab)
		return (NULL);
	sgq = 0;
	dbq = 0;
	inword = 0;

	i = -1;
	while (*str)
	{
		get_words_iter(&i, tab, *str, &sgq, &dbq, &inword);
		str++;
	}
	i++;
	tab[i] = NULL;
	return (tab);
}

*/

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
				if (tab[i] == NULL)
					return (NULL);
				tab[i][0] = '\0';
				inword = 1;
			}
			tab[i] = join_char_free(tab[i], *str);
			if (tab[i] == NULL)
				return (NULL);
		}
		str++;
	}
	i++;
	tab[i] = NULL;
	return (tab);
}

void	get_words(t_token *tokens)
{
	int		i;
	char	**tmp;

	i = 0;
	if (tokens)
	{
		while(!tokens[i].is_last)
		{
			tmp = get_str_words(tokens[i].str);
			tokens[i].words = tmp;
			i++;
		}
	}
}
