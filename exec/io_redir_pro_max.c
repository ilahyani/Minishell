/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redir_pro_max.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:29:30 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/07 17:54:56 by ilahyani         ###   ########.fr       */
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
	int			i;

	data_init(data);
	if (cmd->type == WORD)
	{
		data->cmd = malloc (sizeof(char *) * (sizeof_array(cmd->cmd) + 1));
		if (!(data->cmd))
			return (ft_putendl_fd("Allocation failed", 2), 1);
		i = -1;
		while (cmd->cmd[++i])
			data->cmd[i] = ft_strdup(cmd->cmd[i]);
		data->cmd[i] = NULL;
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
	struct stat	buf;

	if (cmd->type == OUT_REDIR)
	{
		if (!fstat((data)->out_red, &buf))
			if (close((data)->out_red) == -1)
				return (ft_putendl_fd("unexpected error", 2), 1);
		(data)->out_red = open(cmd->cmd[0], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	}
	else if (cmd->type == RE_ADD)
	{
		if (!fstat((data)->out_red, &buf))
			if (close((data)->out_red) == -1)
				return (ft_putendl_fd("unexpected error", 2), 1);
		(data)->out_red = open(cmd->cmd[0], O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
	}
	else if (cmd->type == IN_REDIR)
	{
		if (!fstat((data)->in_red, &buf))
			if (close((data)->in_red) == -1)
				return (ft_putendl_fd("unexpected error", 2), 1);
		(data)->in_red = open(cmd->cmd[0], O_RDONLY, S_IRWXU);
	}
	return (0);
}

int	set_heredoc_fd(t_redir *data, t_env *lst_env, t_node *cmd)
{
	int			p_fd[2];
	char		*line;
	struct stat	buf;

	set_signals("heredoc");
	rl_event_hook = event;
	(data)->her_doc = cmd->cmd[0];
	if (pipe(p_fd) == -1)
		return (ft_putendl_fd("Here_Doc error", 2), 1);
	while (1)
	{
		line = readline("> ");
		if (g_status == -1)
			return (1);
		if (!line || !ft_strcmp(line, (data)->her_doc))
			break ;
		if (ft_strchr(line, '$'))
			print_fd(lst_env, line, p_fd[1]);
		else
			ft_putendl_fd(line, p_fd[1]);
	}
	if (!fstat((data)->in_red, &buf))
		if (close((data)->in_red) == -1)
			return (ft_putendl_fd("unexpected error", 2), 1);
	if ((data)->in_red != -1)
		(data)->in_red = p_fd[0];
	if (close(p_fd[1]) == -1)
		return (ft_putendl_fd("unexpected error", 2), 1);
	return (free(line), 0);
}
