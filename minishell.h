#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

int	ft_strcmp(const char *s1, const char *s2);
int my_echo(int ac, char *av);
int my_cd(int ac, char *av);
int my_pwd(int ac, char *av);

# endif