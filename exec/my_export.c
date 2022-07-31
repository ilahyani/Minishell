/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:19:30 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/31 22:29:06 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_export(char **data, t_env *env)
{
	t_env	*sorted;
	t_env	*lst_tmp;
	int		i;

	if (!env)
		return (0);
	sorted = NULL;
	sorted = lst_copy(env);
	ft_sort(sorted);
	if (sizeof_array(data) == 1)
		env_print(sorted);
	else
	{
		i = 0;
		while (data[++i])
		{
			if (data[i][0] == '_' && (data[i][1] == '=' || data[i][1] == '+'))
				return (1);
			if (check_error(data[i]))
				return (err_print(data[i], "not a valid identifier"), 1);
			if (data[i + 1])
				while (data[i + 1] && !ft_strcmp(data[i], data[i + 1]))
					i++;
			lst_tmp = env;
			while (lst_tmp)
			{
				if (check_var(data[i], lst_tmp))
					break ;
				lst_tmp = lst_tmp->next;
			}
			if (lst_tmp && !find_char(data[i], '='))
				continue ;
			else if (lst_tmp)
				update_exp(data[i], &lst_tmp);
			else
				env_lstadd_back(&env, exprt_lstnew(data[i]));
		}
	}
	/* free(sorted); */
	return (0);
}


