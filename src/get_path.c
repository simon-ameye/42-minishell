/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:17:57 by sameye            #+#    #+#             */
/*   Updated: 2022/01/03 17:04:39 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;

static void	print_command_not_found(char *fnct)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(fnct, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	g_exitval = 127;
}

static char	*get_test_path(char *path, char *fnct)
{
	char	*testpath1;
	char	*testpath2;

	testpath1 = ft_strjoin(path, "/");
	testpath2 = ft_strjoin(testpath1, fnct);
	if (testpath1)
		free(testpath1);
	return (testpath2);
}

static char	*get_path_env(char *fnct, char **env)
{
	int		i;
	char	**paths;
	char	*testpath;

	paths = find_paths(env);
	if (paths)
	{
		i = 0;
		while (paths[i])
		{
			testpath = get_test_path(paths[i], fnct);
			if (!testpath || access(testpath, F_OK) == 0)
			{
				free_str_tab(paths);
				return (testpath);
			}
			if (testpath)
				free(testpath);
			i++;
		}
		free_str_tab(paths);
	}
	print_command_not_found(fnct);
	return (NULL);
}

static char	*get_proc_path(char *cmd, char **env)
{
	if (cmd != NULL)
	{
		if (cmd[0] == '/' || cmd[0] == '.' || cmd[0] == '~' || cmd[0] == '\0')
		{
			if (!ft_strcmp(cmd, ".") || !ft_strcmp(cmd, ".."))
			{
				print_command_not_found(cmd);
				return (NULL);
			}
			else if (cmd[0] == '\0' || access(cmd, F_OK) != 0)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(cmd, STDERR_FILENO);
				ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
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
	return (EXIT_SUCCESS);
}
