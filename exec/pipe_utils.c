/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:52:31 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/11 19:16:46 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redir(t_node *node)
{
	if (node->type == WORD)
		node = node->next;
	if (node && (node->type == HERE_DOC || node->type == IN_REDIR))
		return (1);
	if (node && (node->type == OUT_REDIR || node->type == RE_ADD))
		return (1);
	return (0);
}

int	check_out_redir(t_node *node)
{
	t_node	*tmp;

	tmp = node;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == OUT_REDIR || tmp->type == RE_ADD)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	check_heredoc(t_node *node)
{
	t_node	*tmp;

	tmp = node;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == HERE_DOC)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	is_last(t_node *node)
{
	t_node	*tmp;

	tmp = node;
	if (!(tmp->next))
		return (1);
	while (tmp && check_redir(tmp))
		tmp = tmp->next;
	if (!tmp)
		return (1);
	return (0);
}

void	set_status(int j, int s_in)
{
	int	status;

	while (j--)
		wait(&status);
	g_status = WEXITSTATUS(status);
	s_in_reset(s_in);
}
