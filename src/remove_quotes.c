#include "minishell.h"

char	*remove_quotes_str(char *str)
{
	int		i;
	char	*res;
	char	quote;

	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (res == NULL)
		return (NULL); //free + exit
	quote = 0;
	i = 0;
	while (*str)
	{
		if (*str != '"' && *str != '\'') // pas une quote, on ecrit
			res[i++] = *str;
		else if (!quote) // une quot et on etait pas dans des quotes, on zappe et on entre dans des quotes
			quote = *str;
		else if (*str == quote)//une quote et on etait dans la meme quote, on sort de la quote et on ecrit pas
			quote = 0;
		else if (*str != quote)//une quote et on etait pas dans la meme quote, on ecrit, c est pas une quote
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
