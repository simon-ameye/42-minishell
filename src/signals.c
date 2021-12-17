/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:59:19 by trobin            #+#    #+#             */
/*   Updated: 2021/12/17 16:17:36 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exitval;

/*
 *
 *	In bash, SIGQUIT do _not_ print "Quit (core dumped)" on stdout nor stderr.
 *	For minishell, we arbitrarily decided to print it on stderr.
 *
 */
void	signal_handler(int signum, siginfo_t *siginfo, void *context)
{
	(void)context;
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (siginfo->si_pid != 0)
			rl_redisplay();
		g_exitval = 130;
	}
	else if (signum == SIGQUIT)
	{
		if (siginfo->si_pid == 0)
		{
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
			g_exitval = 131;
		}
		else
		{
			write(1, "\b \b", 3);
			write(1, "\b \b", 3);
		}
	}
}

/*
 *
 *	Initialiser correctement tous les champs:
 *
 *	struct sigaction act = {
 *		.sa_flags = SA_SIGINFO, // call 'sa_sigaction' instead of 'sa_handler'
 *		.sa_sigaction = &signal_handler
 *	};
 *
 *	... mais interdit par la norme !
 *
 * 	Initialise correctement le champ se_mask (sigset_t):
 * 	(Evite les warning de valgrind)
 *
 *	sigemptyset(&act.sa_mask);
 *
 *	... mais fonction interdite par le sujet !
 *
 *
 *
 *	Un processus fils herite de la struct sigaction de son processus pere.
 *	Il peut ensuite modifier cette copie sans toucher a l'originale.
 *
 *	Toutefois, si un processus appelle execve (comme c'est le cas dans ce
 *	minishell pour toute execution de fonction non builtin) alors sa
 *	struct sigaction et reinitialisee avec les valeurs par defaut.
 *
 *
 */
void	init_signals(void)
{
	struct sigaction	act;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &signal_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
