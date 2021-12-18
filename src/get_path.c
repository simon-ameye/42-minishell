/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:17:57 by sameye            #+#    #+#             */
/*   Updated: 2021/12/18 16:25:22 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;

static char	**find_paths(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

static char	*get_path_env(char *fnct, char **env)
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
	ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
	ft_putstr_fd(fnct, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_exitval = 127;
	return (NULL);
}

static char	*get_proc_path(char *cmd, char **env)
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
				g_exitval = 127;
				return (NULL);
			}
			return (ft_strdup(cmd));
		}
		else
			return (get_path_env(cmd, env));
	}
	return (NULL);
}

int	get_path(t_proc *proc)
{
	int	i;

	if (proc)
	{
		if (proc->tokens)
		{
			i = 0;
			while (proc->tokens[i].word)
			{
				if (proc->tokens[i].type == FUNCTION
					&& proc->ftype == EXECVE)
				{
					proc->path = get_proc_path(proc->tokens[i].word, *proc->env);
					if (!proc->path)
						return (EXIT_FAILURE);
				}
				i++;
			}
		}
	}
	return (EXIT_SUCCESS);
}
