#include "minishell.h"

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

static int	ft_isspace(int c)
{
	if ((char)c == ' ' || (char)c == '\t' || (char)c == '\n'
	|| (char)c == '\v' || (char)c == '\f' || (char)c == '\r')
		return (1);
	return (0);
}

static int	custom_ft_atoi(const char *s)
{
	int		i;
	char	sign;
	long	result;

	i = 0;
	while (ft_isspace(s[i]))
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

void	builtin_exit(t_token *token)
{
	int	exit_args;
	int	exit_value;

	exit_args = length_2d_array(token->words) - 1;
	exit_value = custom_ft_atoi(token->words[1]);
	if (exit_args > 1)
	{
		if (exit_value > -1)
		{
			printf("exit\n"); //stderr
			free_tokens(token);
			printf("minishell: exit: too many arguments\n"); //stderr
		}
		else
		{
			printf("minishell: exit: %s: numeric argument required\n", token->words[1]);
			free_tokens(token);
			exit(42);
		}
	}
	if (exit_args == 1)
	{
		if (exit_value > -1 && exit_value < 256)
		{
			printf("exit\n"); //stderr
			free_tokens(token);
			exit(exit_value);
		}
		else
		{
			printf("exit\n"); //stderr
			free_tokens(token);
			exit(42); // undefined behavior (cf. man exit)
		}
	}
}
