/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:28:16 by mjlem             #+#    #+#             */
/*   Updated: 2022/08/08 02:40:56 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*lst_new(char	*arg, int type)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	node->arg = arg;
	node->type = type;
	node->next = NULL;
	return (node);
}

void	add_lst(t_token **head, t_token *node)
{
	t_token	*tmp;

	tmp = (*head);
	if (!(*head))
		(*head) = node;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

t_node	*new_node(int type, char **arg)
{
	t_node	*node;

	node = malloc (sizeof(t_node));
	node->type = type;
	node->cmd = arg;
	node->next = NULL;
	return (node);
}

void	add_node_parse(t_node **head, t_node *node)
{
	t_node	*tmp;

	tmp = (*head);
	if (!(*head))
		(*head) = node;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

void	cmd_error(t_node *cmd)
{
	printf("syntax error\n");
	free_cmd(cmd);
}
