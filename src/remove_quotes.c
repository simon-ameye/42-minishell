#include "minishell.h"

char	*remove_quotes_str(char *str)
{
	int		i;
	char	*res;
	char	quote;

	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (res == NULL)
		return (NULL);
	quote = 0;
	i = 0;
	while (*str)
	{
		if (*str != '"' && *str != '\'')
			res[i++] = *str;
		else if (!quote)
			quote = *str;
		else if (*str == quote)
			quote = 0;
		else if (*str != quote)
			res[i++] = *str;
		str++;
	}
	res[i] = '\0';
	return (res);
}

int	remove_quotes(t_proc proc)
{
	int		i;
	char	*tmp;

	if (proc.tokens)
	{
		i = 0;
		while (proc.tokens[i].word)
		{
			if (proc.tokens[i].type != LIMITOR)
			{
				tmp = remove_quotes_str(proc.tokens[i].word);
				if (!tmp)
					return (EXIT_FAILURE);
				free(proc.tokens[i].word);
				proc.tokens[i].word = tmp;
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
