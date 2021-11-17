#include "minishell.h"

/*
// node types (parser)
#define PIPE	0
#define CMD		1
#define LESS	2
#define GREAT	3

typedef struct	s_ast_node
{
	// node type
	int		type;
	// adjacent nodes
	t_node	*up;
	t_node	*left;
	t_node	*right;
	// IO
	int		input;
	int		output;

}				t_ast_node;
*/

int main()
{
	char	*line;
	t_token	*tokens;

	while (1)
	{
		line = NULL;
		line = readline("minishell> ");
		if (!line)
			break ;
		tokens = lexer(line);
		lst_print_tokens(tokens);
		free(line);
	}
	return (0);
}
