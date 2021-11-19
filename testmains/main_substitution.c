/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_substitution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:05:54 by sameye            #+#    #+#             */
/*   Updated: 2021/11/19 19:02:21 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	HOW TO USE :
//	make -C libft/ && gcc -Wall -Wextra -Werror testmains/main_substitution.c substitution.c substitution_utils.c -I libft/ -L libft/ -l ft -I. -o main_substitution
//	export TESTVAR=/cust/path in your shell
//	./main_substitution



#include "minishell.h"

void	test(char *str, char * expec, char **envp)
{	char *res;

	(void)expec;
	res = NULL;
	printf("input  : [%s]\n",str);
	res = substitution(str, envp);
	printf("result : [%s]\n", res);
	printf("ref    : [");
	fflush(stdout);
	system(str);
	if (!strcmp(res, expec))
		printf("'\n\033[0;32mOK\033[0m\n\n");
	else
		printf("'\n\033[0;31mNOT OK\033[0m\n\n");
	fflush(stdout);
	free(res);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	//setenv("TESTVAR", "/cust/path", 1);

	test("", "", envp);
	test("aaaaaaaa", "aaaaaaaa", envp);
	test("aaa$TESTVAR", "aaa/cust/path", envp);
	test("$TESTVAR aa", "/cust/path aa", envp);
	test("aaa$TESTVARR", "aaa", envp);
	test("aaa$TESTVARR  bb", "aaa  bb", envp);
	test("aaa$TESTVAR  bb $TESTVAR \"TESTVAR $TESTVAR\" '$TESTVAR'", "aaa/cust/path  bb /cust/path \"TESTVAR /cust/path\" '$TESTVAR'", envp);
	test(" \" $TESTVAR '$TESTVAR'\" ", " \" /cust/path '/cust/path'\" ", envp);
	test(" \" aa$TESTVAR '$TESTVAR\" ", " \" aa/cust/path '/cust/path\" ", envp);
	test("\"", "\"", envp);
	test("\"'$TESTVAR'\"", "\"'/cust/path'\"", envp);
	test("'\"$TESTVAR\"'", "'\"$TESTVAR\"'", envp);
	test("'\"'$TESTVAR'\"'", "'\"'/cust/path'\"'", envp);
	test("\"'\"$TESTVAR\"'\"", "\"'\"/cust/path\"'\"", envp);
	test("''\"'\"$TESTVAR\"'\"''", "''\"'\"/cust/path\"'\"''", envp);
	test("''\"'\"$TESTVAR\"'\"''''", "''\"'\"/cust/path\"'\"''''", envp);
	test("''\"'\"$TESTVAR\"'\"''''\"", "''\"'\"/cust/path\"'\"''''\"", envp);
	test(" \"'' ' ' aa$TESTVAR '$TESTVAR\" ' ' ' ", " \"'' ' ' aa/cust/path '/cust/path\" ' ' ' ", envp);
	test(" \"'' ' '' aa$TESTVAR '$TESTVAR\" ' ' '' ", " \"'' ' '' aa/cust/path '/cust/path\" ' ' '' ", envp);

}