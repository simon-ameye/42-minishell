/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:18:04 by sameye            #+#    #+#             */
/*   Updated: 2021/11/22 16:21:46 by sameye           ###   ########.fr       */
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

void	insert_env_var(char **str, char **res, char *const *env)
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

void	expand_iteration(char **str, char **res,
	char *const *env, int *indbquotes, int *insgquotes)
{
	if (**str == '"' && *insgquotes == 0)
	{
		*indbquotes = 1 - *indbquotes;
		*res = join_char_free(*res, **str);
		(*str)++;
	}
	else if (**str == '\'' && *indbquotes == 0)
	{
		*insgquotes = 1 - *insgquotes;
		*res = join_char_free(*res, **str);
		(*str)++;
	}
	else if (**str == '$' && *insgquotes == 0)
		insert_env_var(str, res, env);
	else
	{
		*res = join_char_free(*res, **str);
		(*str)++;
	}
}

char	*dollar_expand_str(char *str, char *const *env)
{
	int		indbquotes;
	int		insgquotes;
	char	*res;

	if (!str || !env)
		return (NULL);
	if (!*env)
		return (ft_strdup(str));
	res = ft_strdup("");
	indbquotes = 0;
	insgquotes = 0;
	while (*str)
		expand_iteration(&str, &res, env, &indbquotes, &insgquotes);
	if (indbquotes)
	{
		ft_putstr_fd("Error : double quote not closed\n", STDERR_FILENO);
		//	free + exit
	}
	return (res);
}

void	dollar_expand(t_token *tokens, char *const *env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	if (tokens)
	{
		while (!tokens[i].is_last)
		{
			j = 0;
			while (tokens[i].words[j])
			{
				tmp = dollar_expand_str(tokens[i].str, env);
				free(tokens[i].str);
				tokens[i].str = tmp;
			}
			i++;
		}
	}
}
