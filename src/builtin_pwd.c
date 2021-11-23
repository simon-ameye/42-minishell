#include "minishell.h"

void	builtin_pwd(t_token *tokens, t_token *token)
{
	if (length_2d_array(token->words) == 1)
		ft_putstr_fd(getcwd(NULL, 0), STDOUT_FILENO);
	else
		ft_putstr_fd("pwd: too many arguments\n", STDERR_FILENO);
}
