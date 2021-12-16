/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:18:04 by sameye            #+#    #+#             */
/*   Updated: 2021/12/16 20:58:26 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;

static char	*join_char_free(char *str, char c)
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

static void	threat_dollar_quest_mark(char **res, char **str)
{
	char	*varval;

	varval = ft_itoa(g_exitval);
	*res = ft_strjoinfree(*res, varval);
	*str += 2;
}

static void	threat_dollar_spec_char(char **res, char **str)
{
	*res = join_char_free(*res, **str);
	(*str)++;
}

static void	threat_dollar_expand(char **res, char **str, char **env)
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

static void threat_dollar(char **res, char **str, char **env)
{
	if ((*str)[1] == '?')
		threat_dollar_quest_mark(res, str);
	else if ((*str)[1] == '"' || (*str)[1] == '\'') //La fameuse quote derriere
		*str += 1;                                  //La fameuse quote derriere
	else if ((*str)[1] >= '0' && (*str)[1] <= '9')
		*str += 2;
	else if (!ft_isalnum((*str)[1]))
		threat_dollar_spec_char(res, str);
	else
		threat_dollar_expand(res, str, env);
}

static int	specific_case(char **res)
{
	*res = join_char_free(*res, '$');
	return (3);
}

static void add_single_char(char **res, char **str)
{
	*res = join_char_free(*res, **str);
	(*str)++;
}

char	*dollar_expand_str(char *str, char **env, int heredoc)
{
	char	*res;
	char	quote;

	if (!*env)
		return (ft_strdup(str));
	res = ft_strdup("");
	if (!res)
		return (NULL);
	quote = 0;
	while (*str)
	{
		switch_quote(&quote, *str);
		if (!ft_strncmp("\"$\"", str, 3) && (quote != '\'' || heredoc))
			str += specific_case(&res);
		if (*str == '$' && (quote != '\'' || heredoc))
			threat_dollar(&res, &str, env);
		else
			add_single_char(&res, &str);
		if (!res)
			return (NULL);
	}
	return (res);
}

int	dollar_expand(t_proc proc)
{
	int		i;
	char	*tmp;

	if (proc.tokens)
	{
		i = 0;
		while (proc.tokens[i].word)
		{
			tmp = dollar_expand_str(proc.tokens[i].word, *proc.env, 0);
			if (!tmp)
			{
				ft_putstr_fd("minishell: error: malloc fail\n", STDERR_FILENO);
				return (EXIT_FAILURE);
			}
			if (ft_strcmp(tmp, proc.tokens[i].word) && ft_strncmp(proc.tokens[i].word, "\"$\"", 3))
				proc.tokens[i].expanded = proc.tokens[i].word;
			else
				free(proc.tokens[i].word);
			proc.tokens[i].word = tmp;
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
