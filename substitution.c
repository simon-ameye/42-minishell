#include "minishell.h"

/*
**This version os ft_strjoin is able to join a str to (null)
*/
char	*ft_strjoincustomfree(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return (NULL);
	if (!s2)
		return (s1);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!(str))
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	if (s2)
	{
		while (s2[j] != '\0')
		{
			str[i] = s2[j];
			i++;
			j++;
		}
	}
	str[i] = '\0';
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (str);
}

char	*joincharfree(char *str, char c)
{
	char *res;

	if (!str)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(str) + 2));
	ft_strcpy(res, str);
	res[ft_strlen(str)] = c;
	res[ft_strlen(str) + 1] = '\0';
	free(str);
	return (res);
}

char	*substitution(char *str, char *const *env)
{
	int i;
	int j;
	char *varname;
	char *varval;
	int indbquotes;
	char *res;

	if (!str || !env)
		return (NULL);
	if (!*env)
		return (ft_strdup(str));
	res = ft_strdup("");
	i = 0;
	indbquotes = 0;
	while (str[i])
	{
		//ft_putstr_fd("current string : ", 2);
		//ft_putstr_fd(str, 2);
		//ft_putstr_fd("\n", 2);
		if (str[i] == '"')
		{
			indbquotes = 1 - indbquotes;
			res = joincharfree(res, str[i]);
			i++;
		}
		else if (str[i] == '\'' && !indbquotes)
		{
			res = joincharfree(res, str[i]);
			i++;
			while(str[i] && str[i] != '\'')
			{
				res = joincharfree(res, str[i]);
				i++;
			}
			if (!str[i])
			{
				ft_putstr_fd("Error : simple quote not closed\n", STDERR_FILENO);
				//free + exit
			}
			else
			{
				res = joincharfree(res, str[i]);
				i++;
			}
		}
		else if (str[i] == '$')
		{
			//ft_putstr_fd("dollar found\n", 2);
			i++;
			j = 0;
			while (str[j + i] && ft_isalnum(str[j + i]))
				j++;
			//printf("i : %d, j : %d, str : %s\n", i, j, str);
			//fflush(stdout);
			varname = ft_substr(str, i, j);
			//printf("varname : '%s'\n", varname);
			//fflush(stdout);
			varval = find_var(varname, env);
			//printf("varval : '%s'\n", varval);
			//fflush(stdout);
			if (varname)
				free(varname);
			//if (varval)
			//tmp = strinsertion(str, varval, i, j + 1);
			/*
			ft_putstr_fd("before free pb\n", 2);
			if (str)
				free(str);
			ft_putstr_fd("after free pb\n", 2);
			*/
			res = ft_strjoincustomfree(res, varval);
			//free(res);
			//res = tmp;
			//str = tmp;
			i = i + j;
		}
		else
		{
			res = joincharfree(res, str[i]);
			i++;
		}
	}
	if (indbquotes)
		ft_putstr_fd("Error : unexpected EOF while looking for matching `\"\n", STDERR_FILENO);
		//free + exit
	return (res);
}

char	*find_var(char *str, char *const *env)
{
	char	*ret;
	int		len; 
	
	ret = NULL;
	len = ft_strlen(str);
	//printf("FIND VAR : len : %i\n", len);
	//fflush(stdout);
	
	if (env)
	{
		while (*env)
		{
			//printf("FIND VAR : tried env %s, str %s, len, %i\n", *env, str, len);
			//fflush(stdout);
			if (ft_strnstr(*env, str, len) && *(*env + len) == '=')
				return (ft_strdup(*env + len + 1));
			env++;
		}
	}
	return (ret);
}
