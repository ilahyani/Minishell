/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:41:56 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/25 18:42:01 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
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
//group those based of their files
int     my_echo(char **data, t_env *lst_env, t_env *expand);
int     my_cd(t_env *lst_env, char **data);
int     my_pwd(void);
int     my_export(char **data, t_env *env);
void    my_exit(char **data);
int		my_env(t_env *env, char **data);
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
void    env_init(char **env, t_env **lst_env);
t_env	*exprt_lstnew(char *buff);
int		ft_exec(char **data, t_env *lst_env);
char    *ft_getenv(char *env, t_env *env_list);
char    *ft_strldup(char *src, size_t len);
void    check_cmd(char **cmd, t_env *lst_env, t_env *expand);
int		check_arg(char **args);
t_env   *check_expantion(char **args, t_env *lst_env, t_env *expantion);
void    handler(int signum);
t_env   *check_expantion(char **args, t_env *lst_env, t_env *expantion);
int		check_arg(char **args);
void    add_node(char *buff, t_env **expantion);
void    update_node(char *buff, t_env **expantion);
void	err_print(char *cmd, char *buff);
char	*strjoin_plus(char *s1, char *s2, char *s3);
int		redir_io(char *line, t_env *lst_env, t_env *expand);
void    o_redir(char *data, t_env *lst_env, t_env *expand, int append);
void    i_redir(char *data, t_env *lst_env, t_env *expand);
void    ft_heredoc(char *data, t_env *lst_env, t_env *expand);
void    exec_child(char *cmd, t_env *lst_env, t_env *expand);
char	*get_path(char *cmd, t_env *lst_env);
int		create_process(char *path, char **data, char **env);
char	*strjoin_plus(char *s1, char *s2, char *s3);
char 	**list_to_tab(t_env *lst_env);
void	free_tab(char **tab);
int		ft_pipe(char *line, t_env *lst_env, t_env *expand);
void    print_fd(t_env *expand, t_env *lst_env, char *arg, int fd);

# endif
