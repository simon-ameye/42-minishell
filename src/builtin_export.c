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
			ft_putstr_fd(str, STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}

static void	print_env_sort(char **env)
{
	int i;
	int j;
	char *previous;
	char *actual;

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

static int	get_varnamelen(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
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
		print_env_sort(*proc->env);
	g_exitval = error_occured;
}
