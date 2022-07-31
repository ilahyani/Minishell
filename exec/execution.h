/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:41:56 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/31 16:37:25 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_data
{
	int	status;
	int	sig;
}	t_global;

t_global	g_glob;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	char	**cmd;
	int		in_red;
	int		out_red;
	char	*her_doc;
}	t_redir;

int		my_echo(char **data);
int		my_cd(t_env *lst_env, char **data);
int		my_pwd(void);
int		my_export(char **data, t_env *env);
void	my_exit(char **data);
int		my_env(t_env *env, char **data);
int		my_unset(t_env **env, char **data);

void	env_init(char **env, t_env **lst_env);
void	unset_oldpwd(t_env *lst_env);
void	update_env_var(t_env **lst_env);
void	env_lstadd_back(t_env **lst, t_env *new);
t_env	*env_lstnew(char *var, char *value);
t_env	*env_lstlast(t_env *lst);

int		ft_strcmp(char *s1, char *s2);
int		sizeof_array(char **arr);
int		is_int(char *c);
void	ft_sort(t_env *env);
char	**sort_tab(char **tab);
char	*strchr_plus(const char *s, int c);
void	env_print(t_env	*env);
size_t	ft_strcpy(char *dst, char *src);
int		find_char_2(t_node *cmd, int type);
int		find_char(char *s, char c);
t_env	*exprt_lstnew(char *buff);
int		ft_exec(char **data, t_env *lst_env);
char	*ft_getenv(char *env, t_env *env_list);
char	*ft_strldup(char *src, size_t len);
void	check_cmd(char **cmd, t_env **lst_env);
int		check_arg(char **args);
void	handler(int signum);
int		check_arg(char **args);
void	add_node(char *buff, t_env **expantion);
void	update_node(char *buff, t_env **expantion);
void	err_print(char *cmd, char *buff);
char	*strjoin_plus(char *s1, char *s2, char *s3);
int		redir_io(t_node *cmd, t_env *lst_env);
int		redir_io_pro_max(t_node *cmd, t_env *lst_env);
void	get_data(t_node *cmd, t_redir *data, t_env *lst_env);
int		o_redir(t_node *cmd, t_env *lst_env, int append);
int		i_redir(t_node *cmd, t_env *lst_env);
int		ft_heredoc(t_node *node, t_env *lst_env);
int		multi_redic_check(t_node *cmd);
void	fd_reset(int fd[2]);
char	*check_file(t_node *node);
void	fd_reset(int fd[2]);
void	data_init(t_redir *data);
char	*get_path(char *cmd, t_env *lst_env);
int		create_process(char *path, char **data, char **env);
char	*strjoin_plus(char *s1, char *s2, char *s3);
char	**list_to_tab(t_env *lst_env);
void	free_tab(char **tab);
int		ft_pipe(t_node *node, t_env *lst_env);
void	print_fd(t_env *lst_env, char *arg, int fd);
t_env	*lst_copy(t_env *env);
int		check_error(char *buff);
int		check_var(char *buff, t_env *lst);
void	update_exp(char *buff, t_env **lst);
int		check_redir(t_node *node);
int		check_heredoc(t_node *node);
int		is_last(t_node *node);
void	s_in_reset(int s_in);
void	set_status(int j);
void	exec_child(t_node *node, t_env *lst_env, int fd[2], int s_in);
void	next_cmd(t_node **node);

#	endif
