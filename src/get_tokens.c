/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:08:48 by sameye            #+#    #+#             */
/*   Updated: 2021/11/25 18:56:42 by sameye           ###   ########.fr       */
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

static t_token	*get_proc_tokens(char *str)
{
	int		dbq;
	int		sgq;
	t_token	*tokens;
	int		i;
	int		inword;

	if (!str)
		return (NULL);
	// Add malloc protection
	// Distinguer pour la fonction appelante:
	// - retour pour cause de malloc fail
	// - retour pour cause de str == NULL
	// traiter les double quotes nulles ex "" doit pas faire de mot
	tokens = malloc(sizeof(t_token) * (ft_strlen(str) + 1));
	sgq = 0;
	dbq = 0;
	inword = 0;

	i = -1;
	while (*str)
	{
		if (ft_isblank(*str) && !sgq && !dbq) //skip a character, eventually leave a word
			inword = 0;
		else if (!sgq && !dbq && (*str == '>' || *str == '<')) //if >, split words
		{
			i++;
			tokens[i].word = malloc(sizeof(char) * 3);
			if (tokens[i].word == NULL)
				return (NULL);
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
					return (NULL);
				tokens[i].word[0] = '\0';
				inword = 1;
			}
			tokens[i].word = join_char_free(tokens[i].word, *str);
			if (tokens[i].word == NULL)
				return (NULL);
		}
		str++;
	}
	i++;
	tokens[i].word = NULL;
	fflush(stdout);
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
			i++;
		}
	}
}

/* ************************************************************************** */

/*
//	pass proc in arg instead of str ? no nedd to declare **tab
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

void	thomas_get_words(t_proc *procs)
{
	int		i;
//	char	**tmp;

	i = 0;
	if (procs)
	{
		while(!procs[i].is_last)
		{
//			tmp = get_str_words(procs[i].str);
//			procs[i].words = tmp;
			procs[i].words = get_str_words(procs[i].str);
//			if (procs[i].words == -1)
//			{
//				free_procs(procs);
//				ft_putstr_fd("error malloc\n", STDERR_FILENO);
//				exit (EXIT_FAILURE);
//			}
			i++;
		}
	}
}
*/
