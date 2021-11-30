
#include "minishell.h"

void	builtin_export(t_proc *proc)
{
	int i;

	i = 0;
	while (proc->tokens[i].word)
	{
		if (proc->tokens[i].type == WORD)
			add_line_in_env(proc->env, proc->tokens[i].word);
		i++;
	}
}