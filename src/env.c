/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 13:23:04 by sameye            #+#    #+#             */
/*   Updated: 2021/12/17 13:23:52 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(char ***env)
{
	if (env && *env)
	{
		free_str_tab(*env);
		*env = NULL;
	}
}

int	find_var_in_env(char **env, char *str, int strlen)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, strlen) && env[i][strlen] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	add_line_in_env(char ***env, char *str)
{
	char	**new_env;

	new_env = copy_env(*env);
	if (!new_env)
	{
		free_env(env);
		return ;
	}
	new_env[str_tab_len(*env)] = ft_strdup(str);
	new_env[str_tab_len(*env) + 1] = NULL;
	free_str_tab(*env);
	*env = new_env;
}

char	**copy_env(char **original_env)
{
	char	**env;
	int		i;

	if (!original_env)
		return (NULL);
	env = malloc(sizeof(char *) * (str_tab_len(original_env) + 2));
	if (!env)
		return (NULL);
	i = 0;
	while (original_env[i])
	{
		env[i] = ft_strdup(original_env[i]);
		if (!env[i])
		{
			free_str_tab(env);
			return (NULL);
		}
		i++;
	}
	env[i] = NULL;
	return (env);
}
