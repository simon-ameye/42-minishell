#include "minishell.h"

extern unsigned char	g_exitval;

// move
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

// move
static int	ft_atouchar(const char *s)
{
	int	i;
	int	sign;
	int	result;

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
		if (result * sign < 0 || result * sign > 255)
			return (-1); // outside uchar range
		++i;
	}
	if (s[i])
		return (-2); // wrong numeric format
	return (result * sign);
}

static void	exit_too_many_arguments(t_proc *proc)
{
	if (proc->pid)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	g_exitval = 1;
}

static void	exit_non_numeric_arguments(t_proc *proc, t_proc *procs)
{
	if (proc->pid)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(proc->tokens[1].word, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	free_env(procs->env);
	free_procs(procs);
	rl_clear_history();
	g_exitval = 2;
	exit(g_exitval);
}

static void	exit_valid_scope(t_proc *proc, t_proc *procs, int exit_value)
{
	g_exitval = (unsigned char)exit_value;
	if (proc->pid)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	free_env(procs->env);
	free_procs(procs);
	rl_clear_history();
	exit(g_exitval);
}

static void	exit_invalid_scope(t_proc *proc, t_proc *procs)
{
	if (proc->pid)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	free_env(procs->env);
	free_procs(procs);
	g_exitval = 2;
	rl_clear_history();
	exit(g_exitval);
}

void	builtin_exit(t_proc *proc, t_proc *procs)
{
	int	exit_args;
	int	exit_value;

	exit_args = get_nb_args(proc->tokens);
	if (exit_args == 0)
	{
		if (proc->pid)
			ft_putstr_fd("exit\n", STDERR_FILENO);
		free_env(procs->env);
		close_saved_fd_and_streams(procs);
		free_procs(procs);
		rl_clear_history();
		exit(g_exitval);
	}
	else
	{
		exit_value = ft_atouchar(proc->tokens[1].word);
		if (exit_value == -2)
			return (exit_non_numeric_arguments(proc, procs));
		if (exit_args > 1)
			return (exit_too_many_arguments(proc));
		if (exit_value == -1)
			return (exit_invalid_scope(proc, procs));
		return (exit_valid_scope(proc, procs, exit_value));
	}
}
