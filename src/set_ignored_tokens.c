#include "minishell.h"

void	set_ignored_tokens(t_proc *proc)
{
	int i;

	if (proc->tokens)
	{
		i = 0;
		while (proc->tokens[i].word)
		{
			if (proc->tokens[i].word[0] == '\0')
				proc->tokens[i].type = IGNORED;
			i++;
		}
	}
}
