#include "minishell.h"

/*
 *	Usage
 *
 *	make -C libft && \
 *	gcc -Wall -Wextra -Werror testmains/main_tokenisation.c tokenisation.c -I . -I libft/ -L libft/ -l ft -o main_tokenisation
 *
 */

void	test(char *line)
{
	t_token *tokens;

	tokens = 0;
	tokens = tokenisation(line, NULL);
	if (tokens)
	{
		printf("minishell>[%s]\n", line);
		print_tokens(tokens);
		free_tokens(tokens);
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
