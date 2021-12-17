/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:25:51 by sameye            #+#    #+#             */
/*   Updated: 2021/12/17 12:33:33 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_option_n(char *str)
{
	if (!*str || *str != '-')
		return (0);
	str++;
	if (!*str || *str != 'n')
		return (0);
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

void	skip_n_options(t_token *tokens, int *i, int *n_option)
{
	while (tokens[*i].word && tokens[*i].type == WORD
		&& is_valid_option_n(tokens[*i].word))
	{
		*n_option = 1;
		(*i)++;
	}
}
