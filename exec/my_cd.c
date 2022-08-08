/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:17:12 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/08 06:14:16 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_cd(t_env *lst_env, char **data)
{
	char	*path;
	char	*cwd;

	cwd = NULL;
	if (!data[1])
		path = ft_strdup(ft_getenv("HOME", lst_env));
	else if (!ft_strcmp(data[1], ".") && !getcwd(cwd, sizeof(cwd)))
	{
		free (cwd);
		return (err_print(data[0], "error retrieving current directory"), 1);
	}
	else if (!ft_strcmp(data[1], "-"))
	{
		path = ft_getenv("OLDPWD", lst_env);
		if (!path)
		{
			free(cwd);
			return (ft_putstr_fd("OLDPWD not set\n", 2), 1);
		}
		printf("%s\n", ft_getenv("OLDPWD", lst_env));
	}
	else
		path = ft_strdup(data[1]);
	free(cwd);
	return (exec_cd(lst_env, data, path));
}

void	update_env_cd(t_env *env_list, char *env, char *val)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp && ft_strcmp(tmp->var, env))
		tmp = tmp->next;
	if (tmp && tmp->value)
	{
		free(tmp->value);
		tmp->value = NULL;
		tmp->value = ft_strdup(val);
	}
	else
		env_lstadd_back(&env_list, env_lstnew(env, val));
}

int	exec_cd(t_env *lst_env, char **data, char *path)
{
	char	*cwd;

	cwd = NULL;
	getcwd(cwd, sizeof(cwd));
	update_env_cd(lst_env, "OLDPWD", cwd);
	if (!getcwd(cwd, sizeof(cwd)))
		update_env_cd(lst_env, "OLDPWD", ft_getenv("PWD", lst_env));
	if (chdir(path) != 0)
	{
		free(path);
		free(cwd);
		return (err_print(data[0], "No such file or directory"), 1);
	}
	update_env_cd(lst_env, "PWD", cwd);
	free(path);
	free(cwd);
	return (0);
}
