/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_and_expand_1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 13:49:53 by sameye            #+#    #+#             */
/*   Updated: 2021/12/19 20:54:06 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;

static char	*find_var(char *str, int len, char **env)
{
	char	*ret;

	ret = NULL;
	if (env)
	{
		while (*env)
		{
			if (!ft_strncmp(*env, str, len) && *(*env + len) == '=')
				return (*env + len + 1);
			env++;
		}
	}
	return (ret);
}

static void	threat_dollar_quest_mark(char **res, char **word)
{
	char	*varval;
	char	*tmp;

	varval = ft_itoa(g_exitval);
	if (varval)
	{
		tmp = str_join_size(*res, varval, ft_strlen(*res)
				+ ft_strlen(*word) + ft_strlen(varval) + 1);
		if (*res)
			free(*res);
		*res = tmp;
		free(varval);
	}
	*word += 1;
}

static void	threat_dollar_expand(char **res, char **word, char **env)
{
	char	*varval;
	int		len;
	char	*tmp;

	len = 0;
	while ((*word)[len] && ft_isalnum((*word)[len]))
		len++;
	varval = find_var(*word, len, env);
	if (varval)
	{
		tmp = str_join_size(*res, varval, ft_strlen(*res)
				+ ft_strlen(*word) + ft_strlen(varval) + 1);
		if (*res)
			free(*res);
		*res = tmp;
	}
	*word += len;
}

static void	threat_dollar_special_char(char **res, char **word)
{
	char	*tmp;

	(*res)[ft_strlen(*res)] = '$';
	tmp = str_join_size(*res, "=", ft_strlen(*res) + ft_strlen(*word) + 2);
	if (tmp)
		tmp[ft_strlen(*res)] = **word;
	if (*res)
		free(*res);
	*res = tmp;
	*word += 1;
}

void	dollar_expand(char **res, char **word, char **env)
{
	*word += 1;
	if (!**word || **word == ' ')
		(*res)[ft_strlen(*res)] = '$';
	else if (**word == '?')
		threat_dollar_quest_mark(res, word);
	else if (**word == '"' || **word == '\'')
		*word += 0;
	else if (**word >= '0' && **word <= '9')
		*word += 1;
	else if (!ft_isalnum(**word))
		threat_dollar_special_char(res, word);
	else
		threat_dollar_expand(res, word, env);
}
