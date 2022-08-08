/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:25:33 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/08 05:38:38 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_data(char *data, t_env **env)
{
	t_env	*lst_tmp;

	lst_tmp = *env;
	while (lst_tmp)
	{
		if (check_var(data, lst_tmp))
			break ;
		lst_tmp = lst_tmp->next;
	}
	if (lst_tmp && !find_char(data, '='))
		return ;
	else if (lst_tmp)
		update_exp(data, &lst_tmp);
	else
		env_lstadd_back(env, exprt_lstnew(data));
}

void	free_list(t_env *list)
{
	t_env	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->var);
		free(list->value);
		free(list);
		list = tmp;
	}
}

t_env	*get_list(t_env *env)
{
	t_env	*sorted;

	sorted = NULL;
	if (env)
	{
		sorted = lst_copy(env);
		ft_sort(sorted);
	}
	return (sorted);
}
