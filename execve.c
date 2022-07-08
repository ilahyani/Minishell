/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:19:07 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/08 19:33:02 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char *cmd, t_env *lst_env)
{
	char	**path;
	int		i;

	path = ft_split(ft_getenv("PATH", lst_env), ':');
	i = -1;
	while (path[++i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], cmd); //check for leaks
		if (!access(path[i], F_OK))
			break ;
	}
	return (path[i]);
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
	tmp = lst_env;
	i = 0;
	while (tmp)
	{
		tab[i] = ft_strjoin(tmp->var, "=");
		tab[i] = ft_strjoin(tab[i], tmp->value); //free old value
		tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
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
			return (ft_putstr_fd("error\n", 2), 1);
		g_exit = 0;
	}
	else
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(c_pid, &status, WUNTRACED);
	return (0);
}

int	ft_exec(char **data, t_env *lst_env)
{
	char	*path;
	char	**env;

	env = list_to_tab(lst_env);
	if (data[0][0] == '.')
		create_process(data[0], data, env);
	else
	{
		path = get_path(data[0], lst_env);
		if (!path)
			return (ft_putstr_fd("error\n", 2), 127);
		if (create_process(path, data, env))
		{
			ft_putstr_fd("minisell: ", 2);
            ft_putstr_fd(data[0], 2);
            ft_putstr_fd(": command not found\n", 2);
			g_exit = 127;
			return (g_exit);
		}
	}
	return (0);
}
