/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:17:12 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/12 10:41:54 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_cd(t_env *lst_env, char **data)
{
	char	*path;
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(NULL, sizeof(NULL));
	if (!data[1])
		path = ft_strdup(ft_getenv("HOME", lst_env));
	else if (!ft_strcmp(data[1], ".") && !cwd)
		return (err_print(data[0], "error retrieving current directory"), 1);
	else if (!ft_strcmp(data[1], "-"))
	{
		path = ft_strdup(ft_getenv("OLDPWD", lst_env));
		if (!path)
		{
			free(cwd);
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), 1);
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
	char	*pwd;
	char	*oldpwd;

	oldpwd = NULL;
	oldpwd = getcwd(NULL, sizeof(NULL));
	if (chdir(path))
		return (exit_error(data, path, oldpwd));
	pwd = getcwd(NULL, sizeof(NULL));
	if (!pwd)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putendl_fd("No such file or directory", 2);
		free(pwd);
		pwd = strjoin_plus(ft_getenv("PWD", lst_env), "/", "..");
	}
	update_env_cd(lst_env, "PWD", pwd);
	if (!oldpwd)
		update_env_cd(lst_env, "OLDPWD", pwd);
	update_env_cd(lst_env, "OLDPWD", oldpwd);
	free(pwd);
	free(oldpwd);
	return (free(path), 0);
}

int	exit_error(char **data, char *path, char *oldpwd)
{
	free(path);
	free(oldpwd);
	if (data[1])
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(data[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	err_print(data[0], "HOME not set");
	return (1);
}
