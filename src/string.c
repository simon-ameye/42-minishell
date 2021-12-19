/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:30:28 by sameye            #+#    #+#             */
/*   Updated: 2021/12/19 20:57:34 by sameye           ###   ########.fr       */
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

int	str_tab_len(char *const *env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	switch_quote(char *quote, char c)
{
	int	switched;

	switched = 0;
	if (c == '"' || c == '\'')
	{
		if (!*quote)
		{
			*quote = c;
			switched = 1;
		}
		else if (c == *quote)
		{
			*quote = 0;
			switched = 1;
		}
	}
	return (switched);
}

static void	str_join_size_iter(char *s1, char *s2, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
}

char	*str_join_size(char *s1, char *s2, int size)
{
	char	*str;

	if (!s1)
		return (NULL);
	if (!s2)
		return (s1);
	str = malloc(size + 1);
	if (!(str))
		return (NULL);
	ft_bzero(str, size + 1);
	str_join_size_iter(s1, s2, str);
	return (str);
}
