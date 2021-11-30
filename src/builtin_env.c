#include "minishell.h"

extern	unsigned char	g_exitval;

void	builtin_env(char *const *env)
{
	if (env)
	{
		while (*env)
		{
			ft_putstr_fd(*env, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			env++;
		}
		g_exitval = 1;
	}
}
