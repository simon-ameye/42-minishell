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

void	init_proc(t_proc *proc)
{
	proc->str = NULL;
	proc->path = NULL;
	proc->args = NULL;
	proc->tokens = NULL;
	proc->ftype = 0;
	proc->fdin = -1;
	proc->fdout = -1;
	proc->is_last = 0;
}

char	*get_proc_str(char *line, int proc_index)
{
	int		lo;
	int		hi;
	int		current_proc_index;
	char	quote;

	lo = 0;
	hi = 0;
	current_proc_index = -1;
	while (line[hi])
	{
		if (line[hi] == '\'' || line[hi] == '"')
		{
			quote = line[hi++];
			while (line[hi] && line[hi] != quote)
				hi++;
			// open quote : already check into 'get_nb_procs()'
			if (!line[hi])
				return (NULL);
		}
		else if (line[hi] == '|')
		{
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

void	create_proc(t_proc *procs, char *line, int index)
{
	init_proc(&procs[index]);

	procs[index].str = NULL;
	procs[index].str = get_proc_str(line, index);
	if (procs[index].str == NULL)
		return (free_procs(procs));
}

int	get_nb_procs(char *line)
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

t_proc	*get_procs(char *line)
{
	t_proc	*procs;
	int		nb_procs;
	int		i;
   
	nb_procs = get_nb_procs(line);
	// malloc all procs once
	procs = 0;
	procs = malloc((sizeof(t_proc) * (nb_procs + 1)));
	if (!procs)
		exit(EXIT_FAILURE);
	// fill each proc according to line's content
	i = 0;
	while (i < nb_procs)
	{
		create_proc(procs, line, i);
		i++;
	}
	// overrides default 'false'
	procs[nb_procs].is_last = 1;
	// return first proc (procs array)
	return (procs);
}
