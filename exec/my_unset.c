/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:20:18 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/09 13:38:37 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_unset(t_env **env, char **data)
{
	int		i;

	if (sizeof_array(data) == 1 || !*env)
		return (1);
	i = 0;
	while (data[++i])
	{
		if (find_char(data[i], '=') || (data[i][0] >= '0' && data[i][0] <= '9'))
		{
			ft_putstr_fd("minishell: unset: ", 2);
			ft_putstr_fd(data[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			return (1);
		}
		if ((*env)->var && !ft_strcmp((*env)->var, data[i]))
			remove_head(env);
		else
			remove_node(env, data[i]);
	}
	return (0);
}

void	remove_head(t_env **env)
{
	t_env	*tmp;

	tmp = (*env)->next;
	free((*env)->var);
	free((*env)->value);
	free(*env);
	(*env) = tmp;
}

void	remove_node(t_env **env, char *data)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = *env;
	while (tmp->next && ft_strcmp(tmp->next->var, data))
		tmp = tmp->next;
	if (tmp->next)
	{
		tmp2 = tmp->next;
		tmp->next = tmp->next->next;
		free(tmp2->var);
		free(tmp2->value);
		free(tmp2);
	}
}
