/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 11:03:03 by sameye            #+#    #+#             */
/*   Updated: 2021/12/17 19:40:44 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s, int n)
{
	char	*ret;

	ret = NULL;
	if (s)
	{
		ret = malloc(sizeof(char) * (n + 1));
		if (ret)
		{
			ft_strncpy(ret, s, n);
			ret[n] = '\0';
		}
	}
	return (ret);
}
