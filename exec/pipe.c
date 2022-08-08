/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:53:48 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/08 22:18:08 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pipe(t_node *node, t_env *lst_env)
{
	int		fd[2];
	int		s_in;
	int		j;
	int		status;
	pid_t	c_pid;

	pipe_init(&j, &status, &s_in);
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
			wait(&status);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 57)
			return (1);
		close_fd(fd);
		next_cmd(&node);
	}
	return (set_status(j, s_in), g_status);
}

void	exec_child(t_node *node, t_env *lst_env, int fd[2], int s_in)
{
	int	status;

	status = 0;
	if (check_redir(node))
	{
		if (check_heredoc(node))
		{
			dup2(s_in, STDIN_FILENO);
			close (s_in);
		}
		status = redir_io(node, lst_env);
	}
	if (status)
		exit(1337);
	if (!is_last(node) && check_redir(node) != 2)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
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
	dup2(fd[0], STDIN_FILENO);
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

void	pipe_init(int *j, int *status, int *s_in)
{
	*j = 0;
	*status = 0;
	*s_in = dup(STDIN_FILENO);
	set_signals("pipe");
}
