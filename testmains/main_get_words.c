/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_get_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:09:17 by sameye            #+#    #+#             */
/*   Updated: 2021/11/23 19:11:24 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	HOW TO USE :
//	make -C libft/ && gcc -Wall -Wextra -Werror testmains/main_get_words.c src/get_words.c src/dollar_expand_utils.c  src/minishell_utils.c -I libft/ -I include/ -L libft/ -l ft -I. -o main_get_words
//	valgrind ./main_get_words

#include "minishell.h"

void    print_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
	{
		printf("[%s]", tab[i]);
		i++;
	}
}

void	test(char *str, char * expec)
{	char **tab;

	(void)expec;
	tab = NULL;
	printf("input    : [%s]\n",str);
	tab = get_str_words(str);
	printf("result   : ");
	print_tab(tab);
	printf("\n");
	printf("expected : %s\n\n", expec);
	free_str_tab(tab);
	fflush(stdout);
}

int main(void)
{
	test("  echo \"o\"blabla 'y\"o\"oo sdsf' \"echo lool\"", "[echo][oblabla][y\"o\"oo sdsf][echo lool]");
	test("", "");
	test(" ' ' \" \" h \"p '\" p \" 'p\" \"'\" f ' f ' ", "[ ][ ][h][p '][p][ 'p]['][f][ f ]");
	test("a<a", "[a][<][a]");
	test("<", "[<]");
	test("<<", "[<<]");
	test("a<>a", "[a][<][>][a]");
	test("a<><>>>><<<<aa><aaa>", "[a][<][>][<][>>][>>][<<][<<][aa][>][<][aaa][>]");
	test("'a<a'\"a<<a\"\"'a<a'\"", "[a<aa<<a'a<a']");
}