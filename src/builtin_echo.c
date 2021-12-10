#include "minishell.h"

extern unsigned char	g_exitval;

static int	is_valid_option_n(char *str)
{
	if (!*str || *str != '-')
		return (0);
	str++;
	if (!*str || *str != 'n')
		return (0);
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

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
		while (proc->tokens[i].word && proc->tokens[i].type == WORD && is_valid_option_n(proc->tokens[i].word))
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
