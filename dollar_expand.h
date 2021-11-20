/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expand.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:32:18 by sameye            #+#    #+#             */
/*   Updated: 2021/11/20 10:57:03 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOLLAR_EXPAND_H
# define DOLLAR_EXPAND_H

# include "minishell.h"

char	*find_var(char *str, char *const *env);
void	insert_env_var(char **str, char **res, char *const *env);
void	expand_iteration(char **str, char **res,
			char *const *env, int *indbquotes, int *insgquotes);
char	*dollar_expand(char *str, char *const *env);
void	strjoin_iter(char **str, char **s1, char **s2);
char	*ft_strjoinfree(char *s1, char *s2);
char	*join_char_free(char *str, char c);

#endif