#include "minishell.h"

extern unsigned char	g_exitval;

void	builtin_echo(t_proc *proc)
{
	int i;
	int n_option;

	n_option = 0;
	if (!proc)
		return ;
	i = 0;
	while (proc->tokens[i].word && proc->tokens[i].type != WORD)
		i++;
	if (proc->tokens[i].word)
	{
		while (proc->tokens[i].word && proc->tokens[i].type == WORD && !ft_strcmp(proc->tokens[i].word, "-n")) //handling multiple "-n"
		{
			n_option = 1;
			i++;
		}
		while (proc->tokens[i].word)
		{
			if (proc->tokens[i].type == WORD)
			{
				ft_putstr_fd(proc->tokens[i].word, STDOUT_FILENO);
				i++;
				break ;
			}
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
	}
	if (!n_option)
		ft_putstr_fd("\n", STDOUT_FILENO);
	g_exitval = 0;
}
