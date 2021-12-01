
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
	if (env && *env)
	{
		while(*env)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(*env, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			env++;
		}
	}
}

static char *get_varname(char *str)
{
	int i;
	char *name;

	name = ft_strdup(str);
	if (!name)
		return (NULL);
	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	name[i] = '\0';
	return(name);
}

void	builtin_export(t_proc *proc)
{
	int i;
	int no_argument;
	char	*varname;
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
				varname = get_varname(proc->tokens[i].word);
				if (varname)
				{
					line = find_var_in_env(*proc->env, varname);
					if (line >= 0)
					{
						free((*proc->env)[line]);
						(*proc->env)[line] = ft_strdup(proc->tokens[i].word);
					}
					else
						add_line_in_env(proc->env, proc->tokens[i].word);
					free(varname);
				}
			}
			else
			{
				error_occured = 1;
				ft_putstr_fd("export: ", STDOUT_FILENO);
				ft_putstr_fd(proc->tokens[i].word, STDOUT_FILENO);
				ft_putstr_fd(": not a valid identifier\n", STDOUT_FILENO);
			}
		}
		i++;
	}
	if (no_argument)
		print_env_declare(*proc->env);
	g_exitval = error_occured;
}