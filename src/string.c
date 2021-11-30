/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:30:28 by sameye            #+#    #+#             */
/*   Updated: 2021/11/30 15:13:41 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_tab(char **tab)
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

//This version of ft_strjoin is able to
//join a str to (null) and frees s1  and s2
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

char	*join_char_free(char *str, char c)
{
	char	*res;

	if (!str)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (res == NULL)
	{
		free(str);
		return (NULL);
	}
	ft_strcpy(res, str);
	res[ft_strlen(str)] = c;
	res[ft_strlen(str) + 1] = '\0';
	free(str);
	return (res);
}

int	str_tab_len(char *const *env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}