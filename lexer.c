#include "minishell.h"

void	lst_add_token(t_token **tokens, t_token *token)
{
	t_token	*cur;

	if (*tokens == NULL)
		*tokens = token;
	else
	{
		cur = *tokens;
		while (cur->next)
			cur = cur->next;
		cur->next = token;
	}
}

static void	get_token_val(t_token **tokens, t_token *token, char *str, int i)
{
	if (token)
	{
		token->val = malloc(sizeof(char) * (i));
		if (token->val == NULL)
		{
			lst_clear_tokens(tokens);
			exit(EXIT_FAILURE);
		}
		ft_strncpy(token->val, str, i);
		token->val[i] = '\0';
	}
}

static void get_token_type(t_token *token, char *str)
{
	// | < > << >>
	if (str)
	{
		if (*str == '|' || *str == '<' || *str == '>'
		|| (*str == '>' && *(str + 1) == '>')
		|| (*str == '<' && *(str + 1) == '<'))
			token->type = OPERATOR;
		else
			token->type = COMMAND;
	}
}

int	add_token(t_token **tokens, t_token *token, char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i])
			{
				if (str[i] == '"')
					break;
				i++;
			}
			if (str[i] != '"')
			{
				ft_putstr_fd("Error : double quote not closed\n", STDERR_FILENO);
				lst_clear_tokens(tokens);
				exit(EXIT_FAILURE);
			}
		}
		i++;
	}
	get_token_val(tokens, token, str, i);
	get_token_type(token, str);
	lst_add_token(tokens, token);
	return (i);
}

void	lst_clear_tokens(t_token **tokens)
{
	t_token	*cur;
	t_token	*tmp;

	cur = *tokens;
	while (cur)
	{
		if (cur->val)
			free(cur->val);
		tmp = (t_token *)cur->next;
		free(cur);
		cur = tmp;
	}
	if (tokens)
		free (tokens);
}

void	lst_print_tokens(t_token **token)
{
	t_token *tmp;

	tmp = *token;
	while (tmp)
	{
		printf("val: %s, type: %d, next: %p, address: %p\n", tmp->val, (int)tmp->type, tmp->next, tmp);
		tmp = tmp->next;
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

t_token	**lexer(char *line)
{
	int		i;
	t_token *token;
	t_token	**tokens;

	if (!line)
		return (NULL);
	tokens = malloc(sizeof(t_token *));
	if (!tokens)
		return (NULL);
	i = 0;
	*tokens = NULL;
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