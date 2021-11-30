/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:18:04 by sameye            #+#    #+#             */
/*   Updated: 2021/11/30 16:46:47 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;

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
			if (ft_strnstr(*env, str, len) && *(*env + len) == '=')
				return (ft_strdup(*env + len + 1));
			env++;
		}
	}
	return (ret);
}

static char	*dollar_expand_str(char *str, char **env)
{
	// unifier la notation avec get_str_words()
	int		dbq; // double_quote
	int		sgq; // single_quote
	char	*res;
	int		len;
	char	*varname;
	char	*varval;

	if (!str || !env)
		return (NULL);
	if (!*env)
		return (ft_strdup(str)); // malloc inside can fail !
	res = ft_strdup(""); // same
	dbq = 0;
	sgq = 0;
	while (*str)
	{
		if (*str == '"' && sgq == 0)
		{
			dbq = 1 - dbq;
			res = join_char_free(res, *str);
			str++;
		}
		else if (*str == '\'' && dbq == 0)
		{
			sgq = 1 - sgq;
			res = join_char_free(res, *str);
			str++;
		}
		else if (*str == '$' && sgq == 0)
		{
			if (str[1] == '?')
			{
				varval = ft_itoa(g_exitval);
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
			tmp = dollar_expand_str(proc.tokens[i].word, *proc.env);
			if (!tmp)
				return (EXIT_FAILURE);
			free(proc.tokens[i].word);
			proc.tokens[i].word = tmp;
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
