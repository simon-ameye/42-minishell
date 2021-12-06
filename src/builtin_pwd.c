#include "minishell.h"

extern	unsigned char	g_exitval;

void	builtin_pwd(void)
{
	ft_putstr_fd(getcwd(NULL, 0), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	g_exitval = 0;
}
