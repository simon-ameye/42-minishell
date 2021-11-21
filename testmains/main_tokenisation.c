#include "minishell.h"

/*
 *	see 'test_tokenisation' target in Makefile
 */

static void	free_tokens_str(t_token *tokens)
{
	int	i;

	i = 0;
	if (tokens)
	{
		while(!tokens[i].is_last)
		{
			if (tokens[i].str)
			{
				free(tokens[i].str);
			}
			i++;
		}
		free(tokens);
	}
}

static void	print_tokens_str(t_token *tokens)
{
	int	i;

	i = 0;
	if (tokens)
	{
		while(!tokens[i].is_last)
		{
			if (tokens[i].str)
			{
				//printf("process %d : %s\n", i, tokens[i].str);
				printf("process %d : args : ", i);
			}
			i++;
		}
	}
}

static void	test(char *line)
{
	t_token *tokens;

	tokens = 0;
	tokens = tokenisation(line, NULL);
	if (tokens)
	{
		printf("minishell>[%s]\n", line);
		print_tokens_str(tokens);
		free_tokens_str(tokens);
	}
}

int main()
{
	test("");
	test("echo |");
	test("echo '|'");
	test("echo \"|\"");
	test("echo '\"|\"'");
	test("echo \"'|'\"");
	test("echo \"\"|\"ls\"");
	test("echo \"'| |'\"");
	test("echo '\"| |\"'");
	test("echo '\"| |\"'");
	test("echo '\"'\"|'\"'");
	test("echo \"'\"|'\"'\"");
	test("echo \"'\"|\"'\"");
	test("echo '\"'|'\"'");
	test("ls | echo hello | cat");
	test("ls | echo hello | cat 'he'");
	test("| echo hello |");
	test("|");
	test("|||");
	test("|||");
	test(" | ");
	test("| ");
	return (0);
}
