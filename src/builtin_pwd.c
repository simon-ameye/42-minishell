#include "minishell.h"

// defined also into builtin_exit.c
static int	length_2d_array(char **s)
{
	int	i;

	if (s)
	{
		i = 0;
		while (s[i])
			i++;
		return (i);
	}
	return (-1);
}

void	builtin_pwd(t_proc *proc)
{
	if (length_2d_array(proc->words) == 1)
		ft_putstr_fd(getcwd(NULL, 0), STDOUT_FILENO); // Bizarre ce stdout, ajouter un \n
	else
		ft_putstr_fd("pwd: too many arguments\n", STDERR_FILENO);
}
