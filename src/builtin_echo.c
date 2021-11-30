#include "minishell.h"

extern unsigned char	g_exitval;

void	builtin_echo(t_proc *proc)
{
	int i;

	if (!proc)
		return ;
	i = 0;
	while (proc->tokens[i].word && proc->tokens[i].type != WORD)
		i++;
	if (!proc->tokens[i].word)
		return ;
	if (ft_strcmp(proc->tokens[i].word, "-n"))
	{
		ft_putstr_fd("Error: unsupported echo option\n", STDERR_FILENO);
		return ;
	}
	while (proc->tokens[i].word && proc->tokens[i].type == WORD && !ft_strcmp(proc->tokens[i].word, "-n")) //handling multiple "-n"
		i++;
	while (proc->tokens[i].word)
	{
		if (proc->tokens[i].type == WORD)
			ft_putstr_fd(proc->tokens[i].word, STDOUT_FILENO);
		i++;
	}
	while (proc->tokens[i].word)
	{
		if (proc->tokens[i].type == WORD)
		{
			ft_putstr_fd(" ", STDOUT_FILENO);
			ft_putstr_fd(proc->tokens[i].word, STDOUT_FILENO);
		}
		i++;
	}
	g_exitval = 0;
}
