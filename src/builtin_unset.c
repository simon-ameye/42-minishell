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

static void	free_line_and_stack(char **env, int line)
{
	free(env[line]);
	while (env[line])
	{
		env[line] = env[line + 1];
		line++;
	}
}

void	builtin_unset(t_proc *proc)
{
	int i;
	int line;
	int	error_occured;

	error_occured = 0;
	i = 0;
	while (proc->tokens[i].word)
	{
		if (proc->tokens[i].type == WORD)
		{
			if (is_correct_export_name(proc->tokens[i].word))
			{
				line = find_var_in_env(*proc->env, proc->tokens[i].word, ft_strlen(proc->tokens[i].word));
				if (line >= 0)
					free_line_and_stack(*proc->env, line);
			}
			else
			{
				error_occured = 1;
				ft_putstr_fd("unset: ", STDOUT_FILENO);
				ft_putstr_fd(proc->tokens[i].word, STDOUT_FILENO);
				ft_putstr_fd(": not a valid identifier\n", STDOUT_FILENO);
			}
		}
		i++;
	}
	g_exitval = error_occured;
}
