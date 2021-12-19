/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_and_expand.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 13:49:53 by sameye            #+#    #+#             */
/*   Updated: 2021/12/19 20:06:31 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;


static void	add_char(char *res, char **word)
{
	res[ft_strlen(res)] = **word;
	*word += 1;
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
		tmp = str_join_size(*res, varval, ft_strlen(*res) + ft_strlen(*word) + ft_strlen(varval) + 1);
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
	fprintf(stderr, "varval %s\n", varval);
	if (varval)
	{
		tmp = str_join_size(*res, varval, ft_strlen(*res) + ft_strlen(*word) + ft_strlen(varval) + 1);
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

static void	dollar_expand(char **res, char **word, char **env)
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

static int	init_res(char **res, char *word)
{
	int		word_len;

	word_len = ft_strlen(word);
	*res = malloc(sizeof(char) * (word_len + 1));
	if (*res == NULL)
		return (EXIT_FAILURE);
	ft_bzero(*res, word_len + 1);
	return (EXIT_SUCCESS);
}

static void	threat_silent_quote(char **word, int *quotes_spotted)
{
	*quotes_spotted = 1;
	*word += 1;
}

static char	*remove_quotes_and_expand_str(t_token *token, char **env, int force_single_quote_expand, int force_quote_keep)
{
	char	*res;
	char	quote;
	char	*word;
	int		quotes_spotted;

	word = token->word;
	if (init_res(&res, word))
		return (NULL);
	quote = 0;
	quotes_spotted = 0;
	while (*word)
	{
		if (switch_quote(&quote, *word) && !force_quote_keep)
			threat_silent_quote(&word, &quotes_spotted);
		else if (*word == '$' && (quote != '\'' || force_single_quote_expand))
			dollar_expand(&res, &word, env);
		else
			add_char(res, &word);
		if (!res)
			return (NULL);
	}
	if (!ft_strlen(res) && !quotes_spotted)
		token->type = IGNORED;
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
				tmp = remove_quotes_and_expand_str(&proc.tokens[i], *proc.env, 0, 0);
				fprintf(stderr, "after  remove_quotes_and_expand_str %s, len %i\n", tmp, (int)ft_strlen(tmp));
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
