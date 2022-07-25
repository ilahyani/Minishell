/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:28:16 by mjlem             #+#    #+#             */
/*   Updated: 2022/07/25 16:43:40 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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

void	add_node(t_node **head, t_node *node)
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
