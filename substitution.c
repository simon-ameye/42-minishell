#include "minishell.h"

/*
**This version os ft_strjoin is able to join a str to (null)
*/
char	*ft_strjoincustom(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return (NULL);
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
	return (str);
}


char	*strinsertion(char *base, char *add, int pos, int size)
{
	char *begin;
	char *ending;
	char *res;
	char *tmp;

	//	printf("STRINSERTION : base %s, add %s, pos %i, size %i\n", base, add, pos, size);
	//	fflush(stdout);
	begin = ft_substr(base, 0, pos);
	//	printf("begin %s\n", begin);
	//	fflush(stdout);
	ending = ft_substr(base, pos + size, ft_strlen(base));
	//	printf("ending $%s$\n", ending);
	//	fflush(stdout);
	tmp = ft_strjoincustom(begin, add);
	//	printf("tmp %s\n", tmp);
	//	fflush(stdout);
	res = ft_strjoincustom(tmp, ending);
	//	printf("res %s\n", res);
	//	fflush(stdout);
	if (begin)
		free(begin);
	if (ending)
		free(ending);
	if (tmp)
		free(tmp);
	
	//printf("result of strinsertion $%s$\n", res);
	//	fflush(stdout);
	return (res);
}

char	*substitution(char *str, char *const *env)
{
	int i;
	int j;
	char *varname;
	char *varval;
	char *tmp;
	int indbquotes;

	i = 0;
	indbquotes = 0;
	while (str[i])
	{
		//ft_putstr_fd("current string : ", 2);
		//ft_putstr_fd(str, 2);
		//ft_putstr_fd("\n", 2);
		if (str[i] == '"')
			indbquotes = 1 - indbquotes;
		if (str[i] == '\'' && !indbquotes)
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
			//ft_putstr_fd("dollar found\n", 2);
			//i++;
			j = 0;
			while (str[j + i + 1] && ft_isalnum(str[j + i + 1]))
				j++;
			//printf("i : %d, j : %d, str : %s\n", i, j, str);
			//fflush(stdout);
			varname = ft_substr(str, i + 1, j);
			//printf("varname : '%s'\n", varname);
			//fflush(stdout);
			varval = find_var(varname, env);
			//printf("varval : '%s'\n", varval);
			//fflush(stdout);
			if (varname)
				free(varname);
			//if (varval)
			tmp = strinsertion(str, varval, i, j + 1);
			/*
			ft_putstr_fd("before free pb\n", 2);
			if (str)
				free(str);
			ft_putstr_fd("after free pb\n", 2);
			*/
			str = tmp;
			i = i + j + 1;
		}
		i++;
	}
	if (indbquotes)
		ft_putstr_fd("Error : unexpected EOF while looking for matching `\"\n", STDERR_FILENO);
		//free + exit
	return (str);
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
