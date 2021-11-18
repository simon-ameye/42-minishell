#ifndef SUBSTITUTION_H
# define SUBSTITUTION_H

#include "minishell.h"

char	*find_var(char *str, char *const *env);
char	*substitution(char *str, char *const *env);
char	*strinsertion(char *base, char *add, int pos, int size);

# endif