/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:37:34 by sameye            #+#    #+#             */
/*   Updated: 2021/12/17 12:50:59 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;

static int	is_correct_export_name(char *str)
{
	if (!str)
		return (0);
	if (!(ft_isalpha(*str) || *str == '_'))
		return (0);
	while (*str && *str != '=')
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return (0);
		str++;
	}
	return (1);
}

static int	get_varnamelen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

void	export_var(char ***env, char *word)
{
	int	varnamelen;
	int	line;

	varnamelen = get_varnamelen(word);
	line = find_var_in_env(*env, word, varnamelen);
	if (line >= 0)
	{
		free((*env)[line]);
		(*env)[line] = ft_strdup(word);
	}
	else
		add_line_in_env(env, word);
}

void	builtin_export(t_proc *proc)
{
	int	i;
	int	no_argument;

	g_exitval = 0;
	i = 0;
	no_argument = 1;
	while (proc->tokens[i].word)
	{
		if (proc->tokens[i].type == WORD)
		{
			no_argument = 0;
			if (is_correct_export_name(proc->tokens[i].word))
				export_var(proc->env, proc->tokens[i].word);
			else
			{
				g_exitval = 1;
				ft_putstr_fd("export: ", STDERR_FILENO);
				ft_putstr_fd(proc->tokens[i].word, STDERR_FILENO);
				ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
			}
		}
		i++;
	}
	if (no_argument)
		print_env_sort(*proc->env);
}
