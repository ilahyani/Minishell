/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 22:19:32 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/08 22:20:13 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
