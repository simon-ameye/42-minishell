/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:25:54 by sameye            #+#    #+#             */
/*   Updated: 2021/12/17 12:32:38 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;

static void	skip_non_words(t_token *tokens, int *i)
{
	while (tokens[*i].word && tokens[*i].type != WORD)
		(*i)++;
}

static void	print_one_word(t_token *tokens, int *i)
{
	ft_putstr_fd(tokens[*i].word, STDOUT_FILENO);
	(*i)++;
}

static void	print_next_wds(t_token *tokens, int *i)
{
	while (tokens[*i].word)
	{
		if (tokens[*i].type == WORD)
		{
			ft_putstr_fd(" ", STDOUT_FILENO);
			ft_putstr_fd(tokens[*i].word, STDOUT_FILENO);
		}
		(*i)++;
	}
}

void	builtin_echo(t_proc *proc)
{
	int	i;
	int	n_option;

	if (!proc)
		return ;
	n_option = 0;
	i = 0;
	while (proc->tokens[i].word && proc->tokens[i].type != WORD)
		i++;
	if (proc->tokens[i].word)
	{
		skip_n_options(proc->tokens, &i, &n_option);
		skip_non_words(proc->tokens, &i);
		print_one_word(proc->tokens, &i);
		print_next_wds(proc->tokens, &i);
	}
	if (!n_option)
		ft_putstr_fd("\n", STDOUT_FILENO);
	g_exitval = 0;
}
