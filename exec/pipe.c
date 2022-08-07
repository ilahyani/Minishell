/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:53:48 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/07 17:21:46 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pipe(t_node *node, t_env *lst_env)
{
	int		fd[2];
	int		s_in;
	int		j;
	pid_t	c_pid;

	s_in = dup(0);
	j = 0;
	while (node)
	{
		j++;
		if (pipe(fd) == -1)
			return (1);
		c_pid = fork();
		if (c_pid == -1)
			return (ft_putstr_fd("fork error\n", 2), 1);
		else if (c_pid == 0)
			exec_child(node, lst_env, fd, s_in);
		if (check_heredoc(node))
			wait(NULL);
		dup2(fd[0], STDIN_FILENO);
		close_fd(fd);
		next_cmd(&node);
	}
	set_status(j);
	return (s_in_reset(s_in), g_status);
}

void	exec_child(t_node *node, t_env *lst_env, int fd[2], int s_in)
{
	if (check_redir(node))
	{
		if (check_heredoc(node))
		{
			dup2(s_in, STDIN_FILENO);
			close (s_in);
		}
		redir_io(node, lst_env);
	}
	if (!is_last(node) && check_redir(node) != 2)
		dup2(fd[1], STDOUT_FILENO);
	close_fd(fd);
	check_cmd(node->cmd, &lst_env);
	exit(g_status);
}

void	next_cmd(t_node **node)
{
	(*node) = (*node)->next;
	while (*node && check_redir(*node))
		*node = (*node)->next;
	if (*node && (*node)->type == PIPE)
		*node = (*node)->next;
}

void	close_fd(int fd[2])
{
	if (close(fd[0]) == -1)
	{
		ft_putstr_fd("fork error\n", 2);
		return ;
	}
	if (close(fd[1]) == -1)
	{
		ft_putstr_fd("fork error\n", 2);
		return ;
	}
}
