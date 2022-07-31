/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:57:15 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/31 16:34:39 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
