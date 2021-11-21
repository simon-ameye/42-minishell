/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_words.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:08:52 by sameye            #+#    #+#             */
/*   Updated: 2021/11/21 18:58:42 by trobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_WORDS_H
# define GET_WORDS_H

void    get_words(t_token *tokens);
char	**get_str_words(char *str);
void	free_words(char **tab);

#endif
