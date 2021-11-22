/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:17:57 by sameye            #+#    #+#             */
/*   Updated: 2021/11/22 18:42:40 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**find_paths(char *const *env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5) != NULL)
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

char	*get_path_iter(char *fnct, char *const *env)
{
	int		i;
	char	**paths;
	char	*testpath1;
	char	*testpath2;

	paths = find_paths(env);
	if (paths)
	{
		i = 0;
		while (paths[i])
		{
			testpath1 = ft_strjoin(paths[i], "/");
			testpath2 = ft_strjoin(testpath1, fnct);
			free(testpath1);
			if (access(testpath2, F_OK) == 0)
			{
				free_str_tab(paths);
				return (testpath2);
			}
			free(testpath2);
			i++;
		}
		free_str_tab(paths);
	}
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putstr_fd(fnct, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (NULL);
}

void    get_path(t_token *tokens, char *const *env)
{
	int		i;

	i = 0;
	if (tokens)
	{
		while(!tokens[i].is_last)
		{
			if (tokens[i].words)
			{
				if (tokens[i].words[0] && tokens[i].ftype == EXECVE)
					tokens[i].path = get_path_iter(tokens[i].words[0], env);
			}
			i++;
		}
	}
}