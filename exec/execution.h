/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:41:56 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/13 14:51:10 by ilahyani         ###   ########.fr       */
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

int	g_status;

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
int		flag_check(char *arg);

int		my_cd(t_env *lst_env, char **data);
char	*check_home(t_env *lst_env);
int		exec_cd(t_env *lst_env, char *path);
void	update_env_cd(t_env *env_list, char *env, char *val);
int		exit_error(char *path, char *oldpwd);

int		my_env(t_env *env, char **data);

void	my_exit(char **data);
int		get_status(int arg);

int		my_export(char **data, t_env **env);
t_env	*lst_copy(t_env *env);
void	export_data(char *data, t_env **env);
int		check_error(char *buff);
int		check_var(char *buff, t_env *lst);
void	update_exp(char *buff, t_env **lst);
void	fill_node(char *buff, t_env **lst);
void	ft_sort(t_env *env);
t_env	*exprt_lstnew(char *buff);
void	env_print(t_env	*env);
char	*ft_strldup(char *src, size_t len);
void	free_list(t_env *list);
t_env	*get_list(t_env *env);

int		my_pwd(t_env *lst_env);

int		my_unset(t_env **env, char **data);
void	remove_head(t_env **env);
void	remove_node(t_env **env, char *data);
int		unset_error_check(char *var);

int		ft_exec(char **data, t_env *lst_env);
char	*get_path(char *cmd, t_env *lst_env);
int		create_process(char *path, char **data, char **env);
char	*strjoin_plus(char *s1, char *s2, char *s3);
char	**list_to_tab(t_env *lst_env);
void	run_executable(char **data, char **env);

void	env_init(char **env, t_env **lst_env);
void	unset_oldpwd(t_env *lst_env);
void	update_shlvl(t_env **lst_env);
void	update_pwd(t_env **lst_env);
void	env_lstadd_back(t_env **lst, t_env *new);
t_env	*env_lstnew(char *var, char *value);
t_env	*env_lstlast(t_env *lst);

int		redir_io(t_node *cmd, t_env *lst_env);
int		multi_redic_check(t_node *cmd);
int		redir_type(t_node *node);
int		o_redir(t_node *cmd, int append);
int		i_redir(t_node *cmd);
int		ft_heredoc(t_node *node, t_env *lst_env);
int		event(void);
int		tmpfile_redir(int tmpfd);
int		redir_io_pro_max(t_node *cmd, t_env *lst_env);
int		set_heredoc_fd(t_redir *data, t_env *lst_env, t_node *cmd);
int		set_fd(t_redir *data, t_node *cmd);
int		set_out_redir(t_redir *data, t_node *cmd, int append);
int		set_in_redir(t_redir *data, t_node *cmd);
int		get_data(t_node *cmd, t_redir *data, t_env *lst_env);
void	fd_reset(int fd[2]);
char	*check_file(t_node *node);
void	data_init(t_redir *data);
void	put_error(t_redir data, t_node *cmd);

int		ft_pipe(t_node *node, t_env *lst_env);
void	exec_child(t_node *node, t_env *lst_env, int fd[2], int s_in);
int		check_redir(t_node *node);
int		check_heredoc(t_node *node);
int		check_out_redir(t_node *node);
int		is_last(t_node *node);
void	s_in_reset(int s_in);
void	set_status(int j, int s_in);
void	next_cmd(t_node **node);
void	close_fd(int fd[2]);
void	pipe_init(int *j, int *status, int *s_in);
int		exec_pipe(t_node *cmd, t_env **lst_env);

void	set_signals(char *context);
void	handler(int signum);
void	child_handler(int signum);
void	heredoc_handler(int signum);
void	pipe_handler(int signum);

int		ft_strcmp(char *s1, char *s2);
int		sizeof_array(char **arr);
int		is_int(char *c);
char	*strchr_plus(const char *s, int c);
size_t	ft_strcpy(char *dst, char *src);
int		find_char_2(t_node *cmd, int type);
int		find_char(char *s, char c);
char	*ft_getenv(char *env, t_env *env_list);
int		check_arg(char **args);
void	err_print(char *cmd, char *buff);
void	free_tab(char **tab);
void	print_fd(t_env *lst_env, char *arg, int fd);
int		dollar_sign_here_doc(t_env *lst_env, char *arg, int fd, int i);
#	endif
