/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:57:15 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/08 07:10:23 by ilahyani         ###   ########.fr       */
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
		if (!find_char(env[i], '='))
			continue ;
		buff = ft_split(env[i], '=');
		if (!buff[1])
			env_lstadd_back(lst_env, env_lstnew(buff[0], ""));
		else
			env_lstadd_back(lst_env, env_lstnew(buff[0], buff[1]));
		free_tab(buff);
	}
	update_shlvl(lst_env);
	update_pwd(lst_env);
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

void	update_shlvl(t_env **lst_env)
{
	t_env	*tmp;
	char	*lvl;
	int		new_lvl;

	tmp = *lst_env;
	while (tmp && ft_strcmp(tmp->var, "SHLVL"))
		tmp = tmp->next;
	if (tmp)
	{
		lvl = ft_strdup(tmp->value);
		free(tmp->value);
		new_lvl = ft_atoi(lvl) + 1;
		tmp->value = NULL;
		if (new_lvl < 0)
			new_lvl = 0;
		tmp->value = ft_itoa(new_lvl);
		free(lvl);
		lvl = NULL;
	}
	else
		env_lstadd_back(lst_env, env_lstnew("SHLVL", "1"));
}

void	update_pwd(t_env **lst_env)
{
	t_env	*tmp;
	char	*cwd;

	tmp = *lst_env;
	cwd = getcwd(NULL, sizeof(NULL));
	while (tmp && ft_strcmp(tmp->var, "PWD"))
		tmp = tmp->next;
	if (tmp && tmp->value)
	{
		free(tmp->value);
		tmp->value = ft_strdup(cwd);
	}
	else
		env_lstadd_back(lst_env, env_lstnew("PWD", cwd));
	free(cwd);
}
