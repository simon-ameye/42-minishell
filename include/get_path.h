/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:19:15 by sameye            #+#    #+#             */
/*   Updated: 2021/11/22 18:45:56 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_PATH_H
# define GET_PATH_H

void    get_path(t_token *tokens, char *const *env);
char	*get_path_iter(char *fnct, char *const *env);
char	**find_paths(char *const *env);

#endif