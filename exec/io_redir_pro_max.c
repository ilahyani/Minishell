/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redir_pro_max.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:29:30 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/11 01:55:08 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_io_pro_max(t_node *cmd, t_env *lst_env)
{
	t_redir		data;

	if (!cmd)
		return (1);
	if (get_data(cmd, &data, lst_env))
		return (1);
	if (data.in_red == -1 || data.out_red == -1)
		return (put_error(data, cmd), 1);
	if (data.in_red != -11)
	{
		dup2(data.in_red, STDIN_FILENO);
		if (close(data.in_red) == -1)
			return (ft_putendl_fd("unexpected error", 2), 1);
	}
	if (data.out_red != -11)
	{
		dup2(data.out_red, STDOUT_FILENO);
		if (close(data.out_red) == -1)
			return (ft_putendl_fd("unexpected error", 2), 1);
	}
	return (0);
}

void	put_error(t_redir data, t_node *cmd)
{
	struct stat	buf;

	if (data.in_red == -1)
	{
		if (!fstat(data.out_red, &buf))
			close(data.out_red);
		err_print(cmd->cmd[0], "No such file or directory");
	}
	else if (data.out_red == -1)
	{
		if (!fstat(data.in_red, &buf))
			close(data.in_red);
		err_print(cmd->cmd[0], "Error openning file");
	}
}

int	get_data(t_node *cmd, t_redir *data, t_env *lst_env)
{
	data_init(data);
	if (cmd->type == WORD)
	{
		cmd = cmd->next;
	}
	while (cmd && cmd->type != PIPE)
	{
		if (cmd->type == HERE_DOC && set_heredoc_fd(data, lst_env, cmd))
			return (1);
		else
			if (set_fd(data, cmd))
				return (1);
		cmd = cmd->next;
	}
	return (0);
}

int	set_fd(t_redir *data, t_node *cmd)
{
	if (cmd->type == OUT_REDIR)
	{
		if (set_out_redir(data, cmd, 0) == 1)
			return (1);
		if ((data)->out_red != -1)
			(data)->out_red = set_out_redir(data, cmd, 0);
	}
	else if (cmd->type == RE_ADD)
	{
		if (set_out_redir(data, cmd, 1) == 1)
			return (1);
		if ((data)->out_red != -1)
			(data)->out_red = set_out_redir(data, cmd, 1);
	}
	else if (cmd->type == IN_REDIR)
	{
		if (set_in_redir(data, cmd) == 1)
			return (1);
		if ((data)->in_red != -1)
			(data)->in_red = set_in_redir(data, cmd);
	}
	return (0);
}

int	set_heredoc_fd(t_redir *data, t_env *lst_env, t_node *cmd)
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
		if (!line || !ft_strcmp(line, check_file(cmd)))
		{
			heredoc_here(RESET);
			break ;
		}
		print_fd(lst_env, line, tmpfd);
		free(line);
	}
	if (close(tmpfd) == -1)
		return (ft_putstr_fd("unexpected error\n", 2), 1);
	tmpfd = open("/tmp/tmpfile", O_RDONLY);
	if (tmpfd == -1)
		return (ft_putstr_fd("unexpected error\n", 2), 1);
	if ((data)->in_red != -1)
		(data)->in_red = tmpfd;
	return (free(line), 0);
}
