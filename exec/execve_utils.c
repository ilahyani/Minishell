/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 14:10:42 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/10 14:11:42 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_process(char *path, char **data, char **env)
{
	int		status;
	pid_t	c_pid;

	set_signals(path);
	c_pid = fork();
	if (c_pid == -1)
		return (ft_putstr_fd("fork error\n", 2), 1);
	else if (c_pid == 0)
	{
		if (execve(path, data, env) == -1)
		{
			free_tab(env);
			return (1);
		}
	}
	waitpid(-1, &status, 0);
	if (!WIFSIGNALED(status))
		g_status = WEXITSTATUS(status);
	return (0);
}

char	*get_path(char *cmd, t_env *lst_env)
{
	char	**split_path;
	char	*path;
	char	*tmp;
	int		i;

	split_path = ft_split(ft_getenv("PATH", lst_env), ':');
	if (!split_path)
		return (NULL);
	i = -1;
	while (split_path[++i])
	{
		tmp = ft_strdup(split_path[i]);
		free(split_path[i]);
		split_path[i] = strjoin_plus(tmp, "/", cmd);
		free(tmp);
		if (!access(split_path[i], F_OK))
			break ;
	}
	path = ft_strdup(split_path[i]);
	free_tab(split_path);
	return (path);
}

char	*strjoin_plus(char *s1, char *s2, char *s3)
{
	int		i;
	int		j;
	char	*str;

	if (!s2)
		s2 = ft_strdup("");
	if (!s3)
		s3 = ft_strdup("");
	str = (char *) malloc (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	i = 0;
	while (s3[i])
		str[j++] = s3[i++];
	str[j] = '\0';
	if (!ft_strcmp(s2, ""))
		free(s2);
	if (!ft_strcmp(s3, ""))
		free(s3);
	return (str);
}

char	**list_to_tab(t_env *lst_env)
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
		if (lst_env->value)
			tab[i++] = strjoin_plus(lst_env->var, "=", lst_env->value);
		else
			tab[i++] = strjoin_plus(lst_env->var, NULL, NULL);
		lst_env = lst_env->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	run_executable(char **data, char **env)
{
	if (create_process(data[0], data, env))
	{
		err_print(data[0], "permission denied");
		g_status = 126;
		exit(g_status);
	}
}
