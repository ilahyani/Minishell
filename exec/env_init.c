/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:57:15 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/26 01:57:12 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//TODO: unset oldpwd & export oldpwd(empty) & export pwd=getcwd & increment shlvl

void	env_init(char **env, t_env **lst_env)
{
    int		i;
    char	**buff;

	if (!env)
		return ;
    i = -1;
    while (env[++i])
    {
        buff = ft_split(env[i], '=');
        if (!buff[1])
            buff[1] = NULL;
	    env_lstadd_back(lst_env, env_lstnew(buff[0], buff[1]));
		free_tab(buff);
    }
}

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
