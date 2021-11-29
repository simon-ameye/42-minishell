#include "minishell.h"

/*
 *
 * todo
 *
 * event if we dont exit, set global variable g_exitval accordingly
 *
 */

// defined also into builtin_pwd.c
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

static int	custom_ft_atoi(const char *s)
{
	int		i;
	char	sign;
	long	result;

	i = 0;
	while (s[i] == ' ')
		++i;
	sign = 1;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		++i;
	}
	result = 0;
	while (ft_isdigit(s[i]))
	{
		result = result * 10 + s[i] - 48;
		if (result * sign > 2147483647)
			return (-1);
		if (result * sign < -2147483648)
			return (0);
		++i;
	}
	if (s[i]) // edit here
			return (-1);
	return (result * sign);
}

void	builtin_exit(t_proc *procs, t_proc *proc)
{
	int	exit_args;
	int	exit_value;

	exit_args = length_2d_array(proc->words) - 1;
	exit_value = custom_ft_atoi(proc->words[1]);
	if (exit_args > 1)
	{
		if (exit_value > -1)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
			free_procs(procs);
		}
		else
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(proc->words[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			free_procs(procs);
			exit(42);
		}
	}
	if (exit_args == 1)
	{
		if (exit_value > -1 && exit_value < 256)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			free_procs(procs);
			exit(exit_value);
		}
		else
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			free_procs(procs);
			exit(42); // undefined behavior (cf. man exit)
		}
	}
}
