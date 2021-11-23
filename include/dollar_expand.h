/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expand.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:32:18 by sameye            #+#    #+#             */
/*   Updated: 2021/11/23 11:57:55 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOLLAR_EXPAND_H
# define DOLLAR_EXPAND_H

char	*find_var(char *str, char *const *env);
void	dollar_expand(t_token *tokens, char *const *env, unsigned char	exitval);
char	*dollar_expand_str(char *str, char *const *env, unsigned char	exitval);
void	strjoin_iter(char **str, char **s1, char **s2);
char	*ft_strjoinfree(char *s1, char *s2);
char	*join_char_free(char *str, char c);

#endif
