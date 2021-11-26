#include "minishell.h"

static t_ftype	get_fnct_type_from_token(t_token *tokens)
{
	int i;
	int j;
	static const char* ftypes[] = { "execve", "no_function", "echo" , "cd", "pwd", "export", "unset", "env", "exit", NULL};

	if (tokens)
	{
		i = 0;
		while (tokens[i].word)
		{
			if (tokens[i].type == WORD)
			{
				tokens[i].type = FUNCTION;
				break;
			}
			i++;
		}
		if (tokens[i].word)
		{
			j = 2;
			while (ftypes[j])
			{
				if (!ft_strcmp(ftypes[j], tokens[i].word))
					return (j);
				j++;
			}
		}
		else
			return (NO_FUNCTION);
	}
	return (EXECVE);
}

void	get_fnct_type(t_proc *proc)
{
	if (proc->tokens)
	{
		proc->ftype = get_fnct_type_from_token(proc->tokens);
	}
}