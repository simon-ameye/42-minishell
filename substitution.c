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

//This version of ft_strjoin is able to
//join a str to (null) and frees s1  and s2
void	strjoin_iter(char **str, char **s1, char **s2)
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

char	*joincharfree(char *str, char c)
{
	char	*res;

	if (!str)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(str) + 2));
	ft_strcpy(res, str);
	res[ft_strlen(str)] = c;
	res[ft_strlen(str) + 1] = '\0';
	free(str);
	return (res);
}

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
