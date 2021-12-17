/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:18:04 by sameye            #+#    #+#             */
/*   Updated: 2021/12/17 13:21:39 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	threat_dollar(char **res, char **str, char **env)
{
	if ((*str)[1] == '?')
		threat_dollar_quest_mark(res, str);
	else if ((*str)[1] == '"' || (*str)[1] == '\'')
		*str += 1;
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

static void	add_single_char(char **res, char **str)
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
			if (ft_strcmp(tmp, proc.tokens[i].word)
				&& ft_strncmp(proc.tokens[i].word, "\"$\"", 3))
				proc.tokens[i].expanded = proc.tokens[i].word;
			else
				free(proc.tokens[i].word);
			proc.tokens[i].word = tmp;
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
