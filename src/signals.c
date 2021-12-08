#include "minishell.h"

extern unsigned char	g_exitval;

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
			ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO); // stderr ?
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
	//sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	rl_outstream = stderr; // see: bash 2> file (rien a faire la)
}
