/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:19:30 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/08 22:27:35 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_export(char **data, t_env **env)
{
	t_env	*sorted;
	int		i;

	sorted = get_list(*env);
	if (sorted && sizeof_array(data) == 1)
		env_print(sorted);
	else
	{
		i = 0;
		while (data[++i])
		{
			if (check_error(data[i]))
			{
				free_list(sorted);
				return (err_print(data[i], "not a valid identifier"), 1);
			}
			if (data[i][0] == '_' && (data[i][1] == '=' || data[i][1] == '+'))
				i++;
			if (data[i + 1])
				while (data[i + 1] && !ft_strcmp(data[i], data[i + 1]))
					i++;
			export_data(data[i], env);
		}
	}
	return (free_list(sorted), 0);
}
