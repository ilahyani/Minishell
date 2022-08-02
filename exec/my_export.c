/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:19:30 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/02 04:16:04 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_export(char **data, t_env **env)
{
	t_env	*sorted;
	int		i;

	sorted = NULL;
    if (*env)
    {
	    sorted = lst_copy(*env);
	    ft_sort(sorted); //free(sorted);
    }
	if (sorted && sizeof_array(data) == 1)
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
			export_data(data[i], env);
		}
	}
	return (0);
}

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
    {
        printf("here1\n");
		update_exp(data, &lst_tmp);
    }
	else
    {
        printf("add_back %s\n", data);
		env_lstadd_back(env, exprt_lstnew(data));
        printf("->%s=%s\n", (*env)->var, (*env)->value);
    }
}
