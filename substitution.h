/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:32:18 by sameye            #+#    #+#             */
/*   Updated: 2021/11/19 17:33:31 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBSTITUTION_H
# define SUBSTITUTION_H

# include "minishell.h"

char	*find_var(char *str, char *const *env);
void	quotecopy(char **str, char **res);
void	insertenvvar(char **str, char **res, char *const *env);
void	substitutiteration(char **str, char **res,
			char *const *env, int *indbquotes);
char	*substitution(char *str, char *const *env);
void	strjoin_iter(char **str, char **s1, char **s2);
char	*ft_strjoinfree(char *s1, char *s2);
char	*joincharfree(char *str, char c);

#endif