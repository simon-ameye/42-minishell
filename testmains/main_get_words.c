/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_get_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:09:17 by sameye            #+#    #+#             */
/*   Updated: 2021/11/20 18:51:46 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	HOW TO USE :
//	make -C libft/ && gcc -Wall -Wextra -Werror testmains/main_get_words.c get_words.c dollar_expand_utils.c -I libft/ -L libft/ -l ft -I. -o main_get_words
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
	printf("input  : [%s]\n",str);
	tab = get_str_words(str);
	printf("result   : ");
	print_tab(tab);
	printf("\n");
	printf("expected : %s\n\n", expec);
	free_words(tab);
	fflush(stdout);
}

int main(void)
{
	test("  echo \"o\"blabla 'y\"o\"oo sdsf' \"echo lool\"", "[echo][oblabla][y\"o\"oo sdsf][echo lool]");
	test("", "");
	test(" ' ' \" \" h \"p '\" p \" 'p\" \"'\" f ' f ' ", "[ ][ ][h][p '][p][ 'p]['][f][ f ]");

}