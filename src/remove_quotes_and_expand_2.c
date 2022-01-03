/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_and_expand_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:32:13 by sameye            #+#    #+#             */
/*   Updated: 2022/01/03 14:34:22 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	threat_silent_quote(char **word, int *quotes_spotted)
{
	*quotes_spotted = 1;
	*word += 1;
}

void	add_char(char *res, char **word)
{
	res[ft_strlen(res)] = **word;
	*word += 1;
}
