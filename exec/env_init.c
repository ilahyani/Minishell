/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:57:15 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/28 05:08:24 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_oldpwd(t_env *lst_env)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = lst_env;
	while (tmp->next && ft_strcmp(tmp->next->var, "OLDPWD"))
            tmp = tmp->next;
	if (tmp->next)
	{
		tmp2 = tmp->next;
		tmp->next = tmp->next->next;
		free(tmp2);
	}
}

void	update_env_var(t_env **lst_env)
{
	t_env	*tmp;
	char	*lvl;

	tmp = env_lstlast(*lst_env);
	if (!ft_strcmp(tmp->var, "SHLVL"))
	{
		lvl = ft_strdup(tmp->value);
		free(tmp->value);
		tmp->value = ft_itoa(ft_atoi(lvl) + 1);
		free(lvl);
	}
	else if (!ft_strcmp(tmp->var, "PWD"))
	{
		if (tmp->value)
		{
			free(tmp->value);
			tmp->value = getcwd(NULL, sizeof(NULL));
		}
	}
}

void	env_init(char **env, t_env **lst_env)
{
    int		i;
    char	**buff;

	if (!*env)
		return ;
    i = -1;
    while (env[++i])
    {
        buff = ft_split(env[i], '=');
        if (!buff[1])
            buff[1] = NULL;
	    env_lstadd_back(lst_env, env_lstnew(buff[0], buff[1]));
		update_env_var(lst_env);
		free_tab(buff);
    }
	unset_oldpwd(*lst_env);
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
