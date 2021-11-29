#include "minishell.h"

extern unsigned char	g_exitval;

static char	*ft_strndup(char *s, int n)
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
		}
	}
	return (ret);
}

static void	init_proc(t_proc *proc, char * const *env)
{
	if (proc)
	{
		proc->str = NULL;
		proc->path = NULL;
		proc->tokens = NULL;
		proc->ftype = 0;
		proc->fdin = -1;
		proc->fdout = -1;
		proc->is_last = 0;
		proc->env = env;
	}
}

static char	*get_proc_str(char *line, int proc_index)
{
	int		lo;
	int		hi;
	int		current_proc_index;
	char	quote;

	lo = 0;
	hi = 0;
	current_proc_index = -1;
	//current_proc_index = 0;
	while (line[hi])
	{
		if (line[hi] == '\'' || line[hi] == '"')
		{
			// all this section in a function
			quote = line[hi++];
			while (line[hi] && line[hi] != quote)
				hi++;
			// open quote : already check into 'get_nb_procs()'
			if (!line[hi])
				return (NULL);
		}
		else if (line[hi] == '|')
		{
		//	if (current_proc_index++ == proc_index)
		//		break ;
		//	lo = hi + 1;
			current_proc_index++;
			if (current_proc_index == proc_index)
				break ;
			else
				lo = hi + 1;
		}
		hi++;
	}
	return (ft_strndup(&line[lo], hi - lo));
}

static int	syntax_error_pipe(char *line, int i)
{
	int	j;

	if (line)
	{
		if (i == 0)
			return (1);
		// check before line[i]
		j = i - 1;
		while (line[j] == ' ')
			j--;
		if (!line[j] || line[j] == '|' || line[i] == '<' || line[i] == '>')
			return (1);
		// check after line[i]
		j = i + 1;
		while (line[j] == ' ')
			j++;
		if (!line[j] || line[j] == '|' || line[i] == '<' || line[i] == '>')
			return (1);
	}
	return (0);
}

static int	get_nb_procs(char *line)
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
				g_exitval = 2;
				return (0);
			}
		}
		else if (line[i] == '|')
		{
			if (syntax_error_pipe(line, i))
			{
				printf("minishell: syntax error near unexpected token '|'\n");
				g_exitval = 2;
				return (0);
			}
			ret++;
		}
		i++;
	}
	return (ret);
}

void	get_procs(t_proc **procs, char *line, char * const *env)
{
	int	i;
	int	nb_procs;

	nb_procs = get_nb_procs(line);
	if (nb_procs)
	{
		// malloc procs
		*procs = malloc((sizeof(t_proc) * (nb_procs + 1)));
		if (!*procs)
			exit(EXIT_FAILURE);
		// fill procs
		i = 0;
		while (i < nb_procs)
		{
	//		create_proc(*procs, line, i);
			init_proc(&(*procs)[i], env);
			(*procs)[i].str = get_proc_str(line, i);
			if ((*procs)[i].str == NULL)
			{
				free_procs(*procs);
				printf("Error: malloc fail\n");
				exit(EXIT_FAILURE);
			}
			i++;
		}
		// overrides default 'false'
		(*procs)[nb_procs].is_last = 1;
	}
}
