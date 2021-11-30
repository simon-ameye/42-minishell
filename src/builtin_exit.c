#include "minishell.h"

extern unsigned char	g_exitval;

static int	get_nb_args(t_token *tokens)
{
	int	i;
	int	ret;

	ret = 0;
	if (tokens)
	{
		i = 0;
		while (tokens[i].word)
		{
			if (tokens[i].type == WORD)
				ret++;
			i++;
		}
	}
	return (ret);
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

void	builtin_exit(t_proc *proc, t_proc *procs)
{
	int	exit_args;
	int	exit_value;

	exit_args = get_nb_args(proc->tokens);
	printf("exit_args: %d\n", exit_args);

	if (exit_args == 0)
	{
		// don't modify g_exitval
		ft_putstr_fd("exit\n", STDERR_FILENO);
		free_procs(procs);
		exit(g_exitval);
	}
	if (exit_args > 0)
	{
		exit_value = custom_ft_atoi(proc->tokens[1].word);
		// non numeric argument
		if (exit_value == -1)
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(proc->tokens[1].word, STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			free_procs(procs);
			g_exitval = 2;
			exit(g_exitval);
		}
		// too much arguments
		if (exit_args > 1)
		{
			// don't exit && don't modify g_exitval
			ft_putstr_fd("exit\n", STDERR_FILENO);
			ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
			return ;
		}
		// exit_value in correct range
		if (exit_value > -1 && exit_value < 256)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			free_procs(procs);
			g_exitval = exit_value;
			exit(exit_value);
		}
		// exit_value in incorrect range
		else
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			free_procs(procs);
			g_exitval = 42; // define this in header ?
			exit(g_exitval); // undefined behavior (cf. man exit)
		}
	}
}
