#include "minishell.h"

void	free_env(char ***env)
{
	if (env && *env)
	{
		free_str_tab(*env);
		*env = NULL;
	}
}

int	find_var_in_env(char **env, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], str, ft_strlen(str)) != NULL && env[i][ft_strlen(str)] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	add_line_in_env(char ***env, char *str)
{
	char	**new_env;

	new_env = copy_env(*env);
	new_env[str_tab_len(*env)] = ft_strdup(str);
	new_env[str_tab_len(*env) + 1] = NULL;
	free_str_tab(*env);
	*env = new_env;
}

void	increase_shlvl(char **env)
{
	int	line;
	int oldlvl;
	char *str;
	char *newlvl;

	line = find_var_in_env(env, "SHLVL");
	oldlvl = 0;
	if (line >= 0)
	{
		oldlvl = ft_atoi(&env[line][ft_strlen("SHLVL=")]);
	}
	newlvl = ft_itoa(oldlvl + 1);
	str = ft_strjoin("SHLVL=", newlvl);
	if (str)
	{
		free(env[line]);
		env[line] = str;
	}
	if (newlvl)
		free(newlvl);
}

char	**copy_env(char **original_env)
{
	char **env;
	int i;

	if (!original_env)
		return(NULL);
	env = malloc(sizeof(char *) * (str_tab_len(original_env) + 2)); //add one more line to further add a new line
	if (!env)
		return (NULL);
	i = 0;
	while(original_env[i])
	{
		env[i] = ft_strdup(original_env[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}