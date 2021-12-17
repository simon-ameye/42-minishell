/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:37:37 by sameye            #+#    #+#             */
/*   Updated: 2021/12/17 12:53:56 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env_declare(char *str)
{
	if (str)
	{
		ft_putstr_fd("export ", STDOUT_FILENO);
		while (*str && *str != '=')
		{
			ft_putchar_fd(*str, STDOUT_FILENO);
			str++;
		}
		if (*str == '=')
		{
			ft_putchar_fd(*str, STDOUT_FILENO);
			str++;
			ft_putchar_fd('"', STDOUT_FILENO);
			while (*str)
			{
				if (*str == '$' || *str == '"')
					ft_putchar_fd('\\', STDOUT_FILENO);
				ft_putchar_fd(*str, STDOUT_FILENO);
				str++;
			}
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}

void	print_env_sort(char **env)
{
	int		i;
	int		j;
	char	*previous;
	char	*actual;

	if (env && *env)
	{
		previous = NULL;
		i = 0;
		while (env[i])
		{
			j = 0;
			actual = NULL;
			while (env[j])
			{
				if ((!previous || ft_strcmp(env[j], previous) > 0)
					&& (!actual || ft_strcmp(env[j], actual) < 0))
					actual = env[j];
				j++;
			}
			print_env_declare(actual);
			previous = actual;
			i++;
		}
	}
}
