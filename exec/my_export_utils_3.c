/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export_list_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:43:30 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/31 22:58:53 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*lst_copy(t_env *env)
{
	t_env	*copy;
	t_env	*tmp;

	copy = NULL;
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			env_lstadd_back(&copy, env_lstnew(tmp->var, tmp->value));
		else
			env_lstadd_back(&copy, env_lstnew(tmp->var, NULL));
		tmp = tmp->next;
	}
	return (copy);
}

void	swap_data(t_env *node1, t_env *node2)
{
	char	*var_tmp;
	char	*value_tmp;

	var_tmp = node1->var;
	value_tmp = node1->value;
	node1->var = node2->var;
	node1->value = node2->value;
	node2->var = var_tmp;
	node2->value = value_tmp;
}

void	ft_sort(t_env *env)
{
	t_env	*lst_tmp;
	t_env	*lst_tmp2;

	lst_tmp = env;
	while (lst_tmp->next)
	{
		lst_tmp2 = lst_tmp->next;
		while (lst_tmp2)
		{
			if (ft_strcmp(lst_tmp2->var, lst_tmp->var) < 0)
				swap_data(lst_tmp2, lst_tmp);
			lst_tmp2 = lst_tmp2->next;
		}
		lst_tmp = lst_tmp->next;
	}
}
