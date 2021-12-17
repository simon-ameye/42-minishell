/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expand_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 13:01:13 by sameye            #+#    #+#             */
/*   Updated: 2021/12/17 13:06:59 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;

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

static char	*find_var(char *str, char **env)
{
	char	*ret;
	int		len;

	ret = NULL;
	len = ft_strlen(str);
	if (env)
	{
		while (*env)
		{
			if (!ft_strncmp(*env, str, len) && *(*env + len) == '=')
				return (ft_strdup(*env + len + 1));
			env++;
		}
	}
	return (ret);
}

void	threat_dollar_quest_mark(char **res, char **str)
{
	char	*varval;

	varval = ft_itoa(g_exitval);
	*res = ft_strjoinfree(*res, varval);
	*str += 2;
}

void	threat_dollar_spec_char(char **res, char **str)
{
	*res = join_char_free(*res, **str);
	(*str)++;
}

void	threat_dollar_expand(char **res, char **str, char **env)
{
	char	*varval;
	char	*varname;
	int		len;

	(*str)++;
	len = 0;
	while ((*str)[len] && ft_isalnum((*str)[len]))
		len++;
	varname = ft_substr(*str, 0, len);
	varval = find_var(varname, env);
	if (varname)
		free(varname);
	*res = ft_strjoinfree(*res, varval);
	*str += len;
}
