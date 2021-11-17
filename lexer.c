#include "minishell.h"

void	lst_add_token(t_token *tokens, t_token *token)
{
	t_token	*cur;

	cur = tokens;
	while (cur)
	{
		if (!cur->next)
			cur->next = token;
		cur = cur->next;
	}
}

int	add_token(t_token *tokens, t_token *token, char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '"')
		{
			while (str[i])
			{
				if (str[i] == '"')
					break;
				i++;
			}
			if (str[i] != '"')
				ft_putstr_fd("Error : double quote not closed", STDERR_FILENO);
		}
		i++;
	}
	token->val = malloc(sizeof(char) * (i));
	if (token->val == NULL)
	{
		lst_clear_tokens(tokens);
		exit(EXIT_FAILURE);
	}
	ft_strncpy(token->val, str, i - 1);
	token->val[i] = '\0';
	lst_add_token(tokens, token);
	return (i);
}

void	lst_clear_tokens(t_token *tokens)
{
	t_token	*cur;
	t_token	*tmp;

	cur = tokens;
	while (cur)
	{
		if (cur->val)
			free(cur->val);
		tmp = (t_token *)cur->next;
		free(cur);
		cur = tmp;
	}
}

void	lst_print_tokens(t_token *token)
{
	while (token)
	{
		printf("val: %s, type: %d\n", token->val, (int)token->type);
		token = token->next;
	}
}

t_token	*new_token()
{
	t_token	*token;

	token = NULL;
	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->val = NULL;
	token->type = NIL;
	token->next = NULL;
	return (token);
}

t_token	*lexer(char *line)
{
	int		i;
	t_token *token;
	t_token *tokens;

	if (!line)
		return (NULL);
	i = 0;
	tokens = NULL;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			token = new_token();
			if (token == NULL)
			{
				lst_clear_tokens(tokens);
				return (NULL);
			}
			i += add_token(tokens, token, &line[i]);
		}
		else
			i++;
	}
	return (tokens);
}