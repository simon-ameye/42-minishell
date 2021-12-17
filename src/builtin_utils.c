/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 20:10:25 by trobin            #+#    #+#             */
/*   Updated: 2021/12/17 20:15:14 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_spaces(char *s, int *i)
{
	*i = 0;
	while (s[*i] == ' ')
		(*i)++;
}

static void	get_sign(char *s, int *sign, int *i)
{
	*sign = 1;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

long	ft_atol(char *s)
{
	unsigned long	ret;
	int				i;
	int				sign;

	if (!s)
		return (-1);
	skip_spaces(s, &i);
	if (!s[i])
		return (-1);
	get_sign(s, &sign, &i);
	ret = 0;
	while (ft_isdigit(s[i]))
	{
		ret = ret * 10 + s[i] - 48;
		if ((sign == 1 && ret > LONG_MAX)
			|| (sign == -1 && ret > (unsigned long)(LONG_MAX + 1UL)))
			return (-1);
		i++;
	}
	if (s[i])
		return (-1);
	return ((long)(ret * sign));
}

int	get_nb_args(t_token *tokens)
{
	int	i;
	int	ret;

	ret = 0;
	if (tokens)
	{
		i = 0;
		while (tokens[i].word)
		{
			if (tokens[i].type == WORD)
				ret++;
			i++;
		}
	}
	return (ret);
}
