/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:20:18 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/09 21:32:51 by ilahyani         ###   ########.fr       */
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
		if (unset_error_check(data[i]))
		{
			ft_putstr_fd("minishell: unset: ", 2);
			ft_putstr_fd(data[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			g_status = 1;
			continue ;
		}
		if ((*env)->var && !ft_strcmp((*env)->var, data[i]))
			remove_head(env);
		else
			remove_node(env, data[i]);
	}
	return (g_status);
}

void	remove_head(t_env **env)
{
	t_env	*tmp;

	tmp = (*env)->next;
	free((*env)->var);
	free((*env)->value);
	free(*env);
	(*env) = tmp;
	g_status = 0;
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
	g_status = 0;
}

int	unset_error_check(char *var)
{
	int	i;

	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (1);
	i = 0;
	while (var[++i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_' && var[i])
			return (1);
	}
	return (0);
}