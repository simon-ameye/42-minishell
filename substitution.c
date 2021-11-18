#include "minishell.h"

char	*strinsertion(char *base, char *add, int pos, int size)
{
	char *begin;
	char *ending;
	char *res;
	char *tmp;

	begin = ft_substr(base, 0, pos);
	ending = ft_substr(base, pos + size, ft_strlen(base));
	tmp = ft_strjoin(begin, add);
	res = ft_strjoin(tmp, ending);
	if (begin)
		free(begin);
	if (ending)
		free(ending);
	if (tmp)
		free(tmp);
	return (res);
}

char	*substitution(char *str, char *const *env)
{
	int i;
	int j;
	char *varname;
	char *varval;

	i = 0;
	while (str[i])
	{
		ft_putstr_fd("current string : ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
		if (str[i] == '\'')
		{
			i++;
			while(str[i] && str[i] != '\'')
				i++;
			if (!str[i])
			{
				ft_putstr_fd("Error : simple quote not closed\n", STDERR_FILENO);
				//free + exit
			}
		}
		if (str[i] == '$')
		{
			ft_putstr_fd("dollar found\n", 2);
			i++;
			j = 0;
			while (str[j] && ft_isalnum(str[j]))
				j++;
			printf("i : %d, j : %d\n", i, j);
			fflush(stdout);
			varname = ft_substr(str, 0, i);
			varval = find_var(varname, env);
			if (varname)
				free(varname);
			str = strinsertion(str, varval, i, j);
			i = i + j;
		}
		i++;
	}
	return (str);
}

char	*find_var(char *str, char *const *env)
{
	char	*ret;
	int		len; 
	
	ret = NULL;
	len = ft_strlen(str);
	if (env)
	{
		while (*env)
		{
			if (ft_strncmp(*env, str, len) && *env[len] == '=')
				return (ft_strdup(env[len + 1]));
			env++;
		}
	}
	return (ret);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	printf("input :  %s\n", av[1]);
	printf("result : %s\n", substitution(av[1], envp));
}