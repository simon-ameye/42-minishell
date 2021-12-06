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

static void	print_env_declare(char **env)
{
	int i;

	if (env && *env)
	{
		while(*env)
		{
			i = 0;
			ft_putstr_fd("declare -x ", STDOUT_FILENO);  //SURTOUT CORRIGER L'ERREUR : export | grep BLA Binary file (standard input) matches
			while ((*env)[i] != '=')
			{
				ft_putchar_fd((*env)[i], STDOUT_FILENO);
				i++;
			}
			if ((*env)[i] == '=')
			{
				ft_putchar_fd((*env)[i], STDOUT_FILENO);
				i++;
				ft_putchar_fd('"', STDOUT_FILENO);
				ft_putstr_fd(&(*env)[i], STDOUT_FILENO);
				ft_putchar_fd('"', STDOUT_FILENO);
			}
			ft_putstr_fd("\n", STDOUT_FILENO);
			env++;
		}
	}
}

static int	get_varnamelen(char *str)
{
	int i;
	char *name;

	name = ft_strdup(str);
	if (!name)
		return (0);
	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	return(i);
}

void	builtin_export(t_proc *proc)
{
	int i;
	int no_argument;
	int	varnamelen;
	int	line;
	int	error_occured;

	error_occured = 0;
	i = 0;
	no_argument = 1;
	while (proc->tokens[i].word)
	{
		if (proc->tokens[i].type == WORD)
		{
			no_argument = 0;
			if (is_correct_export_name(proc->tokens[i].word))
			{
				varnamelen = get_varnamelen(proc->tokens[i].word);
				line = find_var_in_env(*proc->env, proc->tokens[i].word, varnamelen);
				if (line >= 0)
				{
					free((*proc->env)[line]);
					(*proc->env)[line] = ft_strdup(proc->tokens[i].word);
				}
				else
					add_line_in_env(proc->env, proc->tokens[i].word);
			}
			else
			{
				error_occured = 1;
				ft_putstr_fd("export: ", STDERR_FILENO);
				ft_putstr_fd(proc->tokens[i].word, STDERR_FILENO);
				ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
			}
		}
		i++;
	}
	if (no_argument)
		print_env_declare(*proc->env);
	g_exitval = error_occured;
}

/*
export BLA=1
export BLA2=
export BLA3
*/