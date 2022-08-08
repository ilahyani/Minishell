/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 00:06:53 by mjlem             #+#    #+#             */
/*   Updated: 2022/08/07 23:21:57 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**join_2d(char **arg1, char **arg2)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	while (arg1[i])
		i++;
	while (arg2[j])
		j++;
	tmp = malloc (sizeof(char *) * (j + i + 1));
	i = -1;
	while (arg1[++i])
		tmp[i] = ft_strdup(arg1[i]);
	j = 0;
	while (arg2[j])
	{
		tmp[i] = ft_strdup(arg2[j++]);
		i++;
	}
	tmp[i] = NULL;
	free_tab(arg1);
	free_tab(arg2);
	return (tmp);
}

t_node	*move_head(t_node *node, t_node	*tmp3, t_node **origin, t_node *head)
{
	if ((*origin)->type != WORD)
	{
		while (tmp3->next != node)
			tmp3 = tmp3->next;
		tmp3->next = node->next;
		node->next = (*origin);
		(*origin) = node;
		return (head);
	}
	else if (head->type != WORD)
	{
		while (tmp3->next != head)
			tmp3 = tmp3->next;
		tmp3->next = node;
		head->next = node->next;
		node->next = head;
		return (node);
	}
	return (NULL);
}

t_node	*move_node(t_node *node, t_node *head, t_node **origin)
{
	t_node	*tmp;
	t_node	*tmp2;
	t_node	*tmp3;

	tmp = head;
	tmp3 = (*origin);
	if ((*origin)->type != WORD)
		return (move_head(node, tmp3, origin, head));
	else if (node != head && head->type == WORD)
	{
		while (tmp && tmp->next && tmp->next->type == WORD)
			tmp = tmp->next;
		tmp2 = tmp;
		while (tmp2 && tmp2->next != node)
			tmp2 = tmp2->next;
		tmp2->next = node->next;
		node->next = tmp->next;
		tmp->next = node;
	}
	else if (head->type != WORD)
		return (move_head(node, tmp3, origin, head));
	return (head);
}

t_node	*join_words(t_node *list)
{
	t_node	*tmp;
	t_node	*tof;
	int		i;
	char	*tmp1;

	tmp = list;
	i = 0;
	tmp1 = NULL;
	while (tmp)
	{
		if (tmp && tmp->next && tmp->type == WORD && tmp->next->type == WORD)
		{
			tmp->cmd = join_2d(tmp->cmd, tmp->next->cmd);
			tof = tmp->next;
			tmp->next = tmp->next->next;
			free(tof);
		}
		else
			tmp = tmp->next;
	}
	return (list);
}

t_node	*adjuste_list(t_node *list)
{
	t_node	*tmp;
	t_node	*tmp2;

	tmp = list;
	tmp2 = list;
	while (tmp)
	{
		while (tmp && tmp->type != PIPE)
		{
			if (tmp->type == WORD)
			{
				tmp2 = move_node(tmp, tmp2, &list);
			}
			tmp = tmp->next;
		}
		if (!tmp)
			break ;
		tmp = tmp->next;
		tmp2 = tmp;
	}
	list = join_words(list);
	return (list);
}
