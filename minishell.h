/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 10:59:51 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/01 17:11:01 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include <limits.h>

int g_exit;

typedef struct s_env
{
	char			*var;
    char            *value;
	struct s_env     *next;
}	t_env;

int     my_echo(char **data, t_env *lst_env, t_env *expand);
int     my_cd(t_env *lst_env, char **data);
int     my_pwd(void);
int     my_export(char **data, t_env *env);
void    my_exit(char **data);
void    my_env(t_env *env);
int		my_unset(t_env *env, char **data);
int     ft_strcmp(char *s1, char *s2);
int     sizeof_array(char **arr);
int     is_int(char *c);
void	ft_sort(t_env *env);
char    **sort_tab(char **tab);
char    **parser(char *line);
char	*strchr_plus(const char *s, int c);
void	env_print(t_env	*env);
size_t	ft_strcpy(char *dst, char *src);
int     find_char(char *s, char c);
t_env	*env_lstlast(t_env *lst);
void	env_lstadd_back(t_env **lst, t_env *new);
t_env	*env_lstnew(char *var, char *value);
t_env	*env_lstnew_plus(char *buff);
int		ft_exec(char **data, t_env *lst_env);
char    *ft_getenv(char *env, t_env *env_list);
char    *ft_strldup(char *src, size_t len);
t_env    *env_init(char **env, t_env *lst_env);
void    check_cmd(char **cmd, t_env *lst_env, t_env *expand);
int		check_arg(char **args);
t_env   *check_expantion(char **args, t_env *lst_env, t_env *expantion);
# endif
