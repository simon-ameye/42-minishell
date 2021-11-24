/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:36:49 by sameye            #+#    #+#             */
/*   Updated: 2021/11/24 16:25:08 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int are_alnums(char *s)
{
	if (s)
	{
		while (*s)
		{
			if (!ft_isalnum(*s))
				return (0);
			s++;
		}
	}
	return (1);
}

//modifier !!: 
static void	check_redir_syntax(t_token *tokens)
{
	int		i;
	int		j;

	if (tokens)
	{
		i = 0;
		while(!tokens[i].is_last)
		{
			j = 0;
			while (tokens[i].words[j])
			{
				if (!ft_strcmp(tokens[i].words[j], ">"))
				{
					if (!are_alnums(tokens[i].words[j + 1]))
					{
						ft_putstr_fd("syntax error near unexpected token >\n", STDERR_FILENO);
						free_tokens(tokens);
						exit(42);
					}
				}
				j++;
			}
			i++;
		}
	}
}

static void	remove_two_words(char **words, int j)
{
	free(words[j]);
	free(words[j + 1]);
	while (words[j + 2])
	{
		words[j] = words[j + 2];
		j++;
	}
	words[j] = NULL;
}

void	get_fds(t_token *tokens)
{
	int		i;
	int		j;

	check_redir_syntax(tokens);
	if (tokens)
	{
		i = 0;
		while(!tokens[i].is_last)
		{
			j = 0;
			while (tokens[i].words)
			{
				if (!ft_strcmp(tokens[i].words[j], ">"))
				{
					tokens[i].fdout = open(tokens[i].words[j + 1], O_CREAT | O_RDWR, 0644);
					if (tokens[i].fdout == -1)
						perror("ERROR :");
					remove_two_words(tokens[i].words, j);
				}
				i--;
			}
			i++;
		}
	}
}

/* ************************************************************************** */

/*

// need substitution a la volee

char	*get_next_word(char *s)
{
	char	*word;

	word = NULL;
	if (s)
	{
		// skip blanks
		while (*s == ' ') // is_blank ?
			s++;
		// next word in within quotes
		if (*s == '\'' || *s == '"')
		{
			word = ft_strndup(s + 1, elem_index(s + 1, *s));
			break ;
		}
		// next word is outside of quotes
		if (*s)
		{
			int i = 0;
			while (!ft_isalnum(s[i]))
				s++;
			if (s[i])
				word = ft_strndup(s, i);
			else
				word = ft_strndup(s, ft_strlen(s));
			break ;
		}
	}
	return (word);
}

void	get_proc_input_filename(t_token *token)
{
	int		i;
	char	quote;

	if (token)
	{
		i = 0;
		while (token->str[i])
		{
			if (line[i] == '\'' || line[i] == '"')
			{
				quote = line[i++];
				while (line[i] && line[i] != quote)
					i++;
			}
			else if (token->str[i] == '<')
			{
				token->in.filename = get_next_word(&token->str[i]);
				//token->in.fd = open(token->in.filename, O_RDONLY);
			}
			i++;
		}
	}
}

*/
