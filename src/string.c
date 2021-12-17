/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:30:28 by sameye            #+#    #+#             */
/*   Updated: 2021/12/17 17:43:08 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
			i++;
		}
		free(tab);
	}
}

static void	strjoin_iter(char **str, char **s1, char **s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*s1)[i] != '\0')
	{
		(*str)[i] = (*s1)[i];
		i++;
	}
	while ((*s2)[j] != '\0')
	{
		(*str)[i] = (*s2)[j];
		i++;
		j++;
	}
	(*str)[i] = '\0';
}

char	*ft_strjoinfree(char *s1, char *s2)
{
	char	*str;

	if (!s1)
		return (NULL);
	if (!s2)
		return (s1);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!(str))
		return (NULL);
	strjoin_iter(&str, &s1, &s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (str);
}

int	str_tab_len(char *const *env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	switch_quote(char *quote, char c)
{
	if (c == '"' || c == '\'')
	{
		if (!*quote)
			*quote = c;
		else if (c == *quote)
			*quote = 0;
	}
}
