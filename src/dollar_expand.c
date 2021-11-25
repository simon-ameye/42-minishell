/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:18:04 by sameye            #+#    #+#             */
/*   Updated: 2021/11/25 12:41:09 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_var(char *str, char *const *env)
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

static char	*dollar_expand_str(char *str, char *const *env, unsigned char	exitval)
{
	// unifier la notation avec get_str_words()
	int		indbquotes; // double_quote
	int		insgquotes; // single_quote
	char	*res;
	int		len;
	char	*varname;
	char	*varval;

	if (!str || !env)
		return (NULL);
	if (!*env)
		return (ft_strdup(str)); // malloc inside can fail !
	res = ft_strdup(""); // same
	indbquotes = 0;
	insgquotes = 0;
	while (*str)
	{
		if (*str == '"' && insgquotes == 0)
		{
			indbquotes = 1 - indbquotes;
			res = join_char_free(res, *str);
			str++;
		}
		else if (*str == '\'' && indbquotes == 0)
		{
			insgquotes = 1 - insgquotes;
			res = join_char_free(res, *str);
			str++;
		}
		else if (*str == '$' && insgquotes == 0)
		{
			if (str[1] == '?')
			{
				varval = ft_itoa(exitval);
				res = ft_strjoinfree(res, varval);
				str += 2;
			}
			else if (!ft_isalnum(str[1]))
			{
				res = join_char_free(res, *str);
				str++;
			}
			else
			{
				str++;
				len = 0;
				while (str[len] && ft_isalnum(str[len]))
					len++;
				varname = ft_substr(str, 0, len);
				varval = find_var(varname, env);
				if (varname)
					free(varname);
				res = ft_strjoinfree(res, varval);
				str += len;
			}
		}
		else
		{
			res = join_char_free(res, *str);
			str++;
		}
	}
	if (indbquotes)
	{
		ft_putstr_fd("Error : double quote not closed\n", STDERR_FILENO);
		//	free + exit
	}
	return (res);
}

void	dollar_expand(t_proc proc, char *const *env, unsigned char	exitval)
{
	int		i;
	char	*tmp;

	if (proc.tokens)
	{
		i = 0;
		while (proc.tokens[i].word)
		{
			tmp = dollar_expand_str(proc.tokens[i].word, env, exitval);
			free(proc.tokens[i].word);
			proc.tokens[i].word = tmp;
			i++;
		}
	}
}
