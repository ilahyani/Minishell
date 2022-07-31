/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:52:31 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/31 23:18:50 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redir(t_node *node)
{
	if (node->type == WORD)
		node = node->next;
	if (node && (node->type == HERE_DOC || node->type == IN_REDIR
			|| node->type == OUT_REDIR || node->type == RE_ADD))
		return (1);
	return (0);
}

int	check_heredoc(t_node *node)
{
	while (node && node->type != PIPE)
	{
		if (node->type == HERE_DOC)
			return (1);
		node = node->next;
	}
	return (0);
}

int	is_last(t_node *node)
{
	if (!(node->next))
		return (1);
	while (check_redir(node))
		node = node->next;
	if (!node)
		return (1);
	return (0);
}

void	s_in_reset(int s_in)
{
	dup2(s_in, STDIN_FILENO);
	close(s_in);
}

void	set_status(int j)
{
	int	status;

	while (j--)
		wait(&status);
	g_glob.status = WEXITSTATUS(status);
}
