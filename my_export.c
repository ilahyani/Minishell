/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:19:30 by ilahyani          #+#    #+#             */
/*   Updated: 2022/06/28 16:43:34 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*lst_copy(t_env *env)
{
	t_env	*copy;
	t_env	*tmp;

	copy = NULL;
	tmp = env;
	while (tmp)
	{
		env_lstadd_back(&copy, env_lstnew(tmp->var, tmp->value));
		tmp = tmp->next;
	}
	return (copy);
}

void	ft_sort(t_env *env)
{
	t_env	*lst_tmp;
	t_env	*lst_tmp2;
	t_env	*lst_tmp3;
    t_env   *tmp;

	lst_tmp2 = env;
    while (lst_tmp2->next)
    {
		lst_tmp = lst_tmp2->next;
        while (lst_tmp->next)
        {
            if (ft_strcmp(lst_tmp2->var, lst_tmp->var) > 0)
            {
				lst_tmp3 = lst_tmp2;
                lst_tmp2 = lst_tmp;
                lst_tmp = lst_tmp3;
            }
            lst_tmp = lst_tmp->next;
        }
        lst_tmp2 = lst_tmp2->next;
    }
    tmp = env;
    while (tmp)
    {
        printf("->%s=%s\n", tmp->var, tmp->value);
        tmp = tmp->next;
    }
}

int my_export(char **data, t_env *env)
{
    t_env  *sorted;

    (void)data;
    sorted = NULL;
    sorted = lst_copy(env);
    ft_sort(sorted);
    return (0);
}
