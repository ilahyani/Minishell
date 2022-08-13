/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:17:12 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/13 15:01:31 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_cd(t_env *lst_env, char **data)
{
	char	*path;
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(NULL, sizeof(NULL));
	if (!data[1] && !check_home(lst_env))
		return (free(cwd), 1);
	else if (!data[1] && check_home(lst_env))
		path = ft_strdup(check_home(lst_env));
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
	return (exec_cd(lst_env, path));
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

int	exec_cd(t_env *lst_env, char *path)
{
	char	*pwd;
	char	*oldpwd;

	oldpwd = NULL;
	oldpwd = getcwd(NULL, sizeof(NULL));
	if (chdir(path))
		return (exit_error(path, oldpwd));
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
	free(path);
	return (0);
}

int	exit_error(char *path, char *oldpwd)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": No such file or directory", 2);
	free(path);
	free(oldpwd);
	return (1);
}

char	*check_home(t_env *lst_env)
{
	char	*home;

	home = ft_getenv("HOME", lst_env);
	if (!home)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), NULL);
	return (home);
}
