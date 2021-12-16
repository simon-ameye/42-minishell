#include "minishell.h"
#include <limits.h> /* LONG_MAX, LONG_MIN */

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
long	ft_atol(char *s)
{
	unsigned long	ret;
	int				i;
	int				sign;

	if (!s)
		return (-2);
	i = 0;
	while (s[i] == ' ')
		i++;
	if (!s[i])
		return (-2);
	sign = 1;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	ret = 0;
	while (ft_isdigit(s[i]))
	{
		ret = ret * 10 + s[i] - 48;
		if ((sign == 1 && ret > LONG_MAX)
		|| (sign == -1 && ret > (unsigned long)(LONG_MAX + 1UL)))
			return (-2);
		i++;
	}
	if (s[i])
		return (-2);
	return ((long)(ret * sign));
}

void	exit_minishell(t_proc *procs)
{
	if (procs && procs->env)
		free_env(procs->env);
	close_saved_fd_and_streams(procs);
	free_procs(procs);
	rl_clear_history();
	exit(g_exitval);
}

// - add char *line ?
// - add char *msg ?
void	new_exit_minishell(t_proc *procs, char ***env)
{
	free_env(env);
	close_saved_fd_and_streams(procs);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	free_procs(procs);
	rl_clear_history();
	exit(g_exitval);
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
	g_exitval = 2;
	exit_minishell(procs);
}

void	builtin_exit(t_proc *proc, t_proc *procs)
{
	int		exit_args;
	long	exit_value;

	exit_args = get_nb_args(proc->tokens);
	if (exit_args == 0)
	{
		if (proc->pid)
			ft_putstr_fd("exit\n", STDERR_FILENO);
		exit_minishell(procs);
	}
	else
	{
		exit_value = ft_atol(proc->tokens[1].word);
		if (exit_value == -2)
			return (exit_non_numeric_arguments(proc, procs));
		if (exit_args > 1)
			return (exit_too_many_arguments(proc));
		if (proc->pid)
			ft_putstr_fd("exit\n", STDERR_FILENO);
		g_exitval = (unsigned char)exit_value;
		return (exit_minishell(procs));
	}
}
