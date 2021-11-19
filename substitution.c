/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:18:04 by sameye            #+#    #+#             */
/*   Updated: 2021/11/19 17:06:26 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_var(char *str, char *const *env)
{
	char	*ret;
	int		len;

	ret = NULL;
	len = ft_strlen(str);
	if (env)
	{
		while (*env)
		{
			if (ft_strnstr(*env, str, len) && *(*env + len) == '=')
				return (ft_strdup(*env + len + 1));
			env++;
		}
	}
	return (ret);
}

void	quotecopy(char **str, char **res)
{
	*res = joincharfree(*res, **str);
	(*str)++;
	while (**str && **str != '\'')
	{
		*res = joincharfree(*res, **str);
		(*str)++;
	}
	if (!**str)
	{
		ft_putstr_fd("Error : simple quote not closed\n", STDERR_FILENO);
		//free + exit
	}
	else
	{
		*res = joincharfree(*res, **str);
		(*str)++;
	}
}

void	insertenvvar(char **str, char **res, char *const *env)
{
	int		len;
	char	*varname;
	char	*varval;

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

void	substitutiteration(char **str, char **res,
	char *const *env, int *indbquotes)
{
	if (**str == '"')
	{
		*indbquotes = 1 - *indbquotes;
		*res = joincharfree(*res, **str);
		(*str)++;
	}
	else if (**str == '\'' && !*indbquotes)
		quotecopy(str, res);
	else if (**str == '$')
		insertenvvar(str, res, env);
	else
	{
		*res = joincharfree(*res, **str);
		(*str)++;
	}
}

char	*substitution(char *str, char *const *env)
{
	int		indbquotes;
	char	*res;

	if (!str || !env)
		return (NULL);
	if (!*env)
		return (ft_strdup(str));
	res = ft_strdup("");
	indbquotes = 0;
	while (*str)
		substitutiteration(&str, &res, env, &indbquotes);
	if (indbquotes)
	{
		ft_putstr_fd("Error : double quote not closed\n", STDERR_FILENO);
		//	free + exit
	}
	return (res);
}
