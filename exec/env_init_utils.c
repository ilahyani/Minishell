/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:21:07 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/31 06:21:44 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_lstlast(t_env *lst)
{
	t_env	*last;

	if (!lst)
		return (0);
	last = lst;
	while (last->next)
		last = last->next;
	return (last);
}

void	env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = env_lstlast(*lst);
	last->next = new;
}

t_env	*env_lstnew(char *var, char *value)
{
	t_env	*res;

	res = (t_env *) malloc (sizeof(t_env));
	if (!res)
		return (0);
	res->var = ft_strdup(var);
    if (value)
        res->value = ft_strdup(value);
    else
        res->value = NULL;
	res->next = NULL;
	return (res);
}
