/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_words.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:08:48 by sameye            #+#    #+#             */
/*   Updated: 2021/11/24 16:29:23 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*
int		is_chevron(char c)
{
	return (c == '>' || c == '<');
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
	// Add malloc protection
	// Distinguer pour la fonction appelante:
	// - retour pour cause de malloc fail
	// - retour pour cause de str == NULL
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
		/*
		else if (!sgq && !dbq && (*str == '>' || *str == '<')) //if bracket, split words
		{
			i++;
			tab[i] = malloc(sizeof(char));
			if (tab[i] == NULL)
				return (NULL);
			tab[i][0] = '\0';
			inword = 0;
			tab[i] = join_char_free(tab[i], *str);
			if (tab[i] == NULL)
				return (NULL);
			if (*str == *(str + 1)) // if double bracket
			{
				tab[i] = join_char_free(tab[i], *str);
				if (tab[i] == NULL)
					return (NULL);
				str++;
			}
		}
		*/
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

/* ************************************************************************** */

/*
//	pass token in arg instead of str ? no nedd to declare **tab
char	**thomas_get_str_words(char *str)
{
//	int		dbq;
//	int		sgq;
	char	quote;
	char	**tab;
	int		i;
	int		inword;

	if (!str)
		return (NULL);
	// add malloc protection
	// all malloc fails return -1
	tab = NULL;
	tab = malloc(sizeof(char *) * (ft_strlen(str) + 1));
	if (tab == NULL)
		return (-1);
//	sgq = 0;
//	dbq = 0;
	quote = 0;
	inword = 0;

	i = -1;
	while (*str)
	{
		//if (ft_isblank(*str) && !sgq && !dbq)
		if (ft_isblank(*str) && quote == 0)
			inword = 0;
	//	else if (*str == '"' && !sgq)
	//		dbq = 1 - dbq;
	//	else if (*str == '\'' && !dbq)
	//		sgq = 1 - sgq;
		else if (*str && *str == quote)
			quote = 0;

		else if (!sgq && !dbq && (*str == '>' || *str == '<')) //if bracket, split words
		{
			i++;
			tab[i] = malloc(sizeof(char));
			if (tab[i] == NULL)
				return (NULL);
			tab[i][0] = '\0';
			inword = 0;
			tab[i] = join_char_free(tab[i], *str);
			if (tab[i] == NULL)
				return (NULL);
			if (*str == *(str + 1)) // if double bracket
			{
				tab[i] = join_char_free(tab[i], *str);
				if (tab[i] == NULL)
					return (NULL);
				str++;
			}
		}
		else
		{
			if (!inword)
			{
				i++;
				tab[i] = malloc(sizeof(char));
				if (tab[i] == NULL)
					return (-1);
				tab[i][0] = '\0';
				inword = 1;
			}
			tab[i] = join_char_free(tab[i], *str);
			if (tab[i] == NULL)
				return (-1);
		}
		str++;
	}
	i++;
	tab[i] = NULL;
	return (tab);
}

void	thomas_get_words(t_token *tokens)
{
	int		i;
//	char	**tmp;

	i = 0;
	if (tokens)
	{
		while(!tokens[i].is_last)
		{
//			tmp = get_str_words(tokens[i].str);
//			tokens[i].words = tmp;
			tokens[i].words = get_str_words(tokens[i].str);
//			if (tokens[i].words == -1)
//			{
//				free_tokens(tokens);
//				ft_putstr_fd("error malloc\n", STDERR_FILENO);
//				exit (EXIT_FAILURE);
//			}
			i++;
		}
	}
}
*/
