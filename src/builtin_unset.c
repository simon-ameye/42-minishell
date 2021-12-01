#include "minishell.h"

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

	i = 0;
	while (proc->tokens[i].word)
	{
		if (proc->tokens[i].type == WORD)
		{
			line = find_var_in_env(*proc->env, proc->tokens[i].word);
			if (line >= 0)
				free_line_and_stack(*proc->env, line);
		}
		i++;
	}
	//g_exitstatus

}
