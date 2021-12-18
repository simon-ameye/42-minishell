/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:08:48 by sameye            #+#    #+#             */
/*   Updated: 2021/12/18 17:03:51 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;

static void init_tokens(t_token *tokens, int len)
{
	int i;

	i = 0;
	while (i <= len - 1)
	{
		tokens[i].word = NULL;
		tokens[i].type = WORD;
		tokens[i].expanded = 0;
		i++;
	}
}

static void init_word(t_word *word)
{
	word->start = 0;
	word->len = 0;
	word->quote = 0;
}

static void	malloc_fail(t_proc *procs)
{
	ft_putstr_fd("minishell: error: malloc fail\n", STDERR_FILENO);
	g_exitval = EXIT_FAILURE;
	exit_minishell(procs, procs->env);
}

void get_tokens(t_proc *procs)
{
	int		i;
	t_word	word;

	if (procs)
	{
		i = 0;
		while (!procs[i].is_last)
		{
			procs[i].tokens = malloc(sizeof(t_token) * (ft_strlen(procs[i].str) + 1));
			if (!procs[i].tokens)
				malloc_fail(procs);
			init_tokens(procs[i].tokens, ft_strlen(procs[i].str) + 1);
			init_word(&word);
			if (get_words(procs[i].tokens, procs[i].str, word))
				malloc_fail(procs);
			i++;
		}
	}
}
