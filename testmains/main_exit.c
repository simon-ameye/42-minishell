#include "minishell.h"

/*
 *
 * Note: cannot multi-test since we exit within builtin_exit()
 *
 */

void	test(char *s)
{
	t_token	*tokens = malloc(sizeof(t_token) * 2);

	init_token(&tokens[0]);
	init_token(&tokens[1]);

	tokens[0].str = ft_strdup(s);
	tokens[1].str = NULL;
	tokens[1].is_last = 1;

	get_words(tokens);
	builtin_exit(tokens);
}

int main()
{
	test("exit 42");
//	test("exit -1");
//	test("exit 9999999999999999999999");
//	test("exit 100 ls");
//	test("exit 100 42");
//	test("exit echo ls");
//	test("exit");
	return (0);
}
