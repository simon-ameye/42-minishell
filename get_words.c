/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_words.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:08:48 by sameye            #+#    #+#             */
/*   Updated: 2021/11/20 12:29:07 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_str_words(char *str)
{
	int		sgquote;
	int		dbquote;
	int		len;
	char	**tab;
	int		i;

	len = ft_strlen(str);
	tab = malloc(sizeof(char *) * (len + 1));
	sgquote = 0;
	dbquote = 0;




	join_char_free()
	

}

void	get_words(t_token **tokens)
{
	char **tab;
	int i;

	tab = get_str_words("  echo blabla 'yooo sdsf' \"echo lool\"");
	i = 0;
	while(tab[i])
	{
		printf(tab[i]);
	}
}

//  hsdhbsdhjcb 'axasx' "dwedw edd"