#include "minishell.h"

char	*custom_ft_strncpy(char *dst, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while (i <= len) // modif: <= instead of <
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

char	*ft_strndup(char *s, int n)
{
	char	*ret;

	ret = NULL;
	if (s)
	{
		ret = malloc(sizeof(char) * (n + 1));
		if (ret)
		{
			ft_strncpy(ret, s, n);
			ret[n] = '\0';
			//custom_ft_strncpy(ret, s, n);
		}
	}
	return (ret);
}

void	init_token(t_token *token, char *const *env)
{
	token->str = NULL;
	token->path = NULL;
	token->args = NULL;
	token->env = env;
	token->ftype = 0; // ?
	token->input = -1;
	token->output = -1;
	token->is_last = 0;
}

void	free_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	if (tokens)
	{
		while(!tokens[i].is_last)
		{
			if (tokens[i].str)
				free(tokens[i].str);
			i++;
		}
		free(tokens);
	}
}

char	*get_token_str(char *line, int token_index)
{
	int		lo;
	int		hi;
	int		current_token_index;
	char	quote;

	lo = 0;
	hi = 0;
	current_token_index = -1;
	while (line[hi])
	{
		if (line[hi] == '\'' || line[hi] == '"')
		{
			quote = line[hi++];
			while (line[hi] && line[hi] != quote)
				hi++;
			// open quote : already check into 'get_nb_tokens()'
			if (!line[hi])
				return (NULL);
		}
		else if (line[hi] == '|')
		{
			current_token_index++;
			if (current_token_index == token_index)
				break ;
			else
				lo = hi + 1;
		}
		hi++;
	}
	return (ft_strndup(&line[lo], hi - lo));
}

void	create_token(t_token *tokens, char *line, int index, char *const *env)
{
	init_token(&tokens[index], env);

	tokens[index].str = NULL;
	tokens[index].str = get_token_str(line, index);
	if (tokens[index].str == NULL)
		return (free_tokens(tokens));
}

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	if (tokens)
	{
		while(!tokens[i].is_last)
		{
			if (tokens[i].str)
				printf("process %d : %s\n", i, tokens[i].str);
			i++;
		}
	}
}

int	get_nb_tokens(char *line)
{
	int		i;
	int		ret;
	char	quote;

	i = 0;
	ret = 1;
	while (line[i])
	{
		// when we encouter a quote,
		// continue until finding the same one
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
			if (!line[i])
			{
				if (quote == '\'')
					printf("Error: simple quote not closed\n");
				else
					printf("Error: double quote not closed\n");
				return (0);
			}
		}
		else if (line[i] == '|')
			ret++;
		i++;
	}
	return (ret);
}

t_token	*tokenisation(char *line, char *const *env)
{
	t_token *tokens;
	int		nb_tokens;
	int		i;
   
	nb_tokens = get_nb_tokens(line);
	// malloc all tokens once
	tokens = 0;
	tokens = malloc((sizeof(t_token) * (nb_tokens + 1)));
	if (!tokens)
		exit(EXIT_FAILURE);
	// fill each token according to line's content
	i = 0;
	while (i < nb_tokens)
	{
		create_token(tokens, line, i, env);
		i++;
	}
	// overrides default 'false'
	tokens[nb_tokens].is_last = 1;
	// return first token (tokens array)
	return (tokens);
}
