/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_and_expand.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 13:49:53 by sameye            #+#    #+#             */
/*   Updated: 2021/12/19 17:10:12 by sameye           ###   ########.fr       */
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

static void	threat_dollar_quest_mark(char **res, int *i, char **word)
{
	char	*varval;

	varval = ft_itoa(g_exitval);
	*res = ft_strjoinfree(*res, varval);
	*i = ft_strlen(*res);
	*word += 1;
}

static void	threat_dollar_spec_char(char **res, int *i, char **word)
{
	*res = join_char_free(*res, **word);
	*word += 1;
	*i += 1;
}

static char	*str_join_size(char *s1, char *s2, int size)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;

	if (!s1)
		return (NULL);
	if (!s2)
		return (s1);
	str = malloc(size + 1);
	if (!(str))
		return (NULL);
	ft_bzero(str, size + 1);
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
	return (str);
}

static void	threat_dollar_expand(char **res, int *i, char **word, char **env)
{
	char	*varval;
	int		len;
	char	*tmp;

	len = 0;
	while ((*word)[len] && ft_isalnum((*word)[len]))
		len++;
	varval = find_var(*word, len, env);
	tmp = str_join_size(*res, varval, ft_strlen(*res) + ft_strlen(*word) + len + 1);
	if (*res)
		free(*res);
	*res = tmp;
	*word += len;
	*i = ft_strlen(*res);
}

static void	dollar_expand(char **res, int *i, char **word, char **env)
{
	if (**word == '?')
		threat_dollar_quest_mark(res, i, word);
	else if (**word == '"' || **word == '\'')
		*word += 0;
	else if (**word >= '0' && **word <= '9')
		*word += 1;
	else if (!ft_isalnum(**word))
		threat_dollar_spec_char(res, i, word);
	else
		threat_dollar_expand(res, i, word, env);
}

static char *remove_quotes_and_expand_str(char *word, char **env)
{
	int		i;
	char	*res;
	char	quote;
	int		word_len;

	word_len = ft_strlen(word);
	res = malloc(sizeof(char) * (word_len + 1));
	if (res == NULL)
		return (NULL);
	ft_bzero(res, word_len + 1);
	quote = 0;
	i = 0;
	while (*word)
	{
		if (switch_quote(&quote, *word))
			word++;
		else if (*word == '$' && quote != '\'')
		{
			word++;
			dollar_expand(&res, &i, &word, env);
		}
		else
		{
			res[i] = *word;
			i++;
			word++;
		}
	}
	return (res);
}

int	remove_quotes_and_expand(t_proc proc)
{
	int		i;
	char	*tmp;

	if (proc.tokens)
	{
		i = 0;
		while (proc.tokens[i].word)
		{
			if (proc.tokens[i].type != LIMITOR)
			{
				fprintf(stderr, "before remove_quotes_and_expand_str %s\n", proc.tokens[i].word);
				tmp = remove_quotes_and_expand_str(proc.tokens[i].word, *proc.env);
				fprintf(stderr, "before remove_quotes_and_expand_str %s\n", tmp);
				if (!tmp)
					return (EXIT_FAILURE);
				if (ft_strcmp(tmp, proc.tokens[i].word)
					&& ft_strncmp(proc.tokens[i].word, "\"$\"", 3))
					proc.tokens[i].expanded = proc.tokens[i].word;
				else
					free(proc.tokens[i].word);
				proc.tokens[i].word = tmp;
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
