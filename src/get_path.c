/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:17:57 by sameye            #+#    #+#             */
/*   Updated: 2021/11/26 18:04:53 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**find_paths(char *const *env)
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

static char	*get_path_env(char *fnct, char *const *env)
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
			if (testpath1)
				free(testpath1);
			if (access(testpath2, F_OK) == 0)
			{
				free_str_tab(paths);
				return (testpath2);
			}
			if (testpath2)
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

static char	*get_proc_path(char *cmd, char *const *env)
{
	if (cmd != NULL)
	{
		if (cmd[0] == '/' || cmd[0] == '.' || cmd[0] == '~')
		{
			if (access(cmd, F_OK) != 0)
			{
				ft_putstr_fd("No such file or directory: ", STDERR_FILENO);
				ft_putstr_fd(cmd, STDERR_FILENO);
				ft_putstr_fd("\n", STDERR_FILENO);
				return (NULL);
			}
			return (ft_strdup(cmd));
		}
		else
			return (get_path_env(cmd, env));
	}
	return (NULL);
}

int	get_path(t_proc *proc, char *const *env)
{
	int	i;

	if (proc)
	{
		if (proc->tokens)
		{
			i = 0;
			while (proc->tokens[i].word)
			{
				if (proc->tokens[i].type == FUNCTION)
				{
					proc->path = get_proc_path(proc->tokens[i].word, env);
					return (EXIT_SUCCESS);	
				}
				i++;
			}
		}
	}
	return (EXIT_SUCCESS);
}
