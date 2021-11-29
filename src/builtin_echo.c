#include "minishell.h"

void	builtin_echo(t_proc *proc)
{
	int i;

	if (!proc)
		return ;
	i = 0;
	while (proc->tokens[i].word)
	{
		if (proc->tokens[i].type == WORD)
		{
			if (ft_strcmp(proc->tokens[i].word, "-n"))
				return ;
			break;
		}
		i++;
	}
	i++;
	while (proc->tokens[i].word)
	{
		if (proc->tokens[i].type == WORD)
			break;
		i++;
	}
	while (proc->tokens[i].word && proc->tokens[i].type == WORD)
	{
		ft_putstr_fd(proc->tokens[i].word, STDOUT_FILENO);
		if (proc->tokens[i + 1].word && proc->tokens[i + 1].type == WORD)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
}