/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:19:07 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/25 21:57:00 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec(char **data, t_env *lst_env)
{
	char	*path;
	char	**env = NULL;

	env = list_to_tab(lst_env);
	if ((data[0][0] == '.' && data[0][1] == '/') || data[0][0] == '/')
		create_process(data[0], data, env);
	else
	{
		path = get_path(data[0], lst_env);
		if (!path)
			return (err_print(data[0], "No such file or directory"), 127);
		else if (create_process(path, data, env))
		{
			ft_putstr_fd("minisell: ", 2);
            ft_putstr_fd(data[0], 2);
            ft_putstr_fd(": command not found\n", 2);
			return (127);
		}
	}
	// free env;
	return (g_exit);
}

int	create_process(char *path, char **data, char **env)
{
	pid_t	c_pid;
	int		status;

	c_pid = fork();
	if (c_pid == -1)
		return (ft_putstr_fd("error\n", 2), 1);
	else if (c_pid == 0)
	{
		if (execve(path, data, env) == -1)
			return (err_print(path, "Command not found"), 1);
	}
	waitpid(-1, &status, 0);
	g_exit = WEXITSTATUS(status);
	return (0);
}

char	*get_path(char *cmd, t_env *lst_env)
{
	char	**path;
	int		i;

	path = ft_split(ft_getenv("PATH", lst_env), ':');
	if (!path)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], cmd);
		if (!access(path[i], F_OK))
			break ;
	}
	//free path
	return (path[i]);
}

char	*strjoin_plus(char *s1, char *s2, char *s3)
{
	int	i;
	int	j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *) malloc (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	i = 0;
	while (s3[i])
		str[j++] = s3[i++];
	str[j] = '\0';
	return (str);
}

char **list_to_tab(t_env *lst_env)
{
	char	**tab;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = lst_env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	tab = (char **) malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (lst_env)
	{
		tab[i++] = strjoin_plus(lst_env->var, "=", lst_env->value);
		lst_env = lst_env->next;
	}
	tab[i] = NULL;
	return (tab);
}
