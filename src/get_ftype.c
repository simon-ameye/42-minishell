/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ftype.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:15:23 by sameye            #+#    #+#             */
/*   Updated: 2021/11/22 12:14:31 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ftype	get_words_ftype(char *str)
{
	int i;
	static const char* ftypes[] = { "execve", "echo" , "cd", "pwd", "export", "unset", "env", "exit", NULL};

	i = 1;
	while (ftypes[i])
	{
		if (!ft_strcmp(ftypes[i], str))
			return (i);
		i++;
	}
	return (EXECVE);
}

void	get_ftype(t_token *tokens)
{
	int		i;

	i = 0;
	if (tokens)
	{
		while(!tokens[i].is_last)
		{
			tokens[i].ftype = get_words_ftype(tokens[i].words[0]);
			i++;
		}
	}
}