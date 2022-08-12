/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 22:39:06 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/12 15:40:18 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_io(t_node *cmd, t_env *lst_env)
{
	if (multi_redic_check(cmd) == 1)
	{
		if (redir_type(cmd) == HERE_DOC)
			return (ft_heredoc(cmd, lst_env));
		else if (redir_type(cmd) == IN_REDIR)
			return (i_redir(cmd));
		else if (redir_type(cmd) == OUT_REDIR)
			return (o_redir(cmd, 0));
		else if (redir_type(cmd) == RE_ADD)
			return (o_redir(cmd, 1));
	}
	return (redir_io_pro_max(cmd, lst_env));
}

int	tmpfile_redir(int tmpfd)
{
	tmpfd = open("/tmp/tmpfile", O_RDONLY);
	if (tmpfd == -1)
		return (ft_putstr_fd("unexpected error\n", 2), 1);
	dup2(tmpfd, STDIN_FILENO);
	if (close(tmpfd) == -1)
		return (ft_putstr_fd("unexpected error\n", 2), 1);
	return (0);
}

int	ft_heredoc(t_node *node, t_env *lst_env)
{
	char	*line;
	int		tmpfd;

	set_signals("heredoc");
	rl_event_hook = event;
	tmpfd = open("/tmp/tmpfile", O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (tmpfd == -1)
		return (ft_putstr_fd("unexpected error\n", 2), 1);
	while (1)
	{
		line = readline("> ");
		if (g_status == -1)
			return (1);
		if (!line || !ft_strcmp(line, check_file(node)))
		{
			heredoc_here(RESET);
			break ;
		}
		print_fd(lst_env, line, tmpfd);
		free(line);
	}
	free(line);
	if (close(tmpfd) == -1)
		return (ft_putstr_fd("unexpected error\n", 2), 1);
	return (tmpfile_redir(tmpfd));
}

int	i_redir(t_node *cmd)
{
	int		redirect_fd;
	char	*file;

	file = check_file(cmd);
	redirect_fd = open(file, O_RDONLY, S_IRWXU);
	if (redirect_fd == -1)
		return (err_print(file, "No such file or directory"), 1);
	dup2(redirect_fd, STDIN_FILENO);
	if (close(redirect_fd) == -1)
		return (ft_putstr_fd("unexpected error\n", 2), 1);
	return (0);
}

int	o_redir(t_node *cmd, int append)
{
	int		redirect_fd;
	char	*file;

	file = check_file(cmd);
	if (append)
		redirect_fd = open(file, O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
	else
		redirect_fd = open(file, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	if (redirect_fd == -1)
		return (err_print(file, "Is a directory"), 1);
	dup2(redirect_fd, STDOUT_FILENO);
	if (close(redirect_fd) == -1)
		return (ft_putstr_fd("unexpected error\n", 2), 1);
	return (0);
}
