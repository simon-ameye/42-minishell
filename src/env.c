#include "minishell.h"

char **copy_env(char *const *original_env)
{
	char **env;
	int i;

	if (!original_env)
		return(NULL);
	env = malloc(sizeof(char *) * (str_tab_len(original_env) + 1));
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