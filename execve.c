/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:19:07 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/01 17:13:40 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **list_to_tab(t_env *lst_env)
{
	char **tab;
	t_env	*tmp;
    char    *char_tmp;
	int	i;

	i = 0;
	tmp = lst_env;
	while (tmp && i++)
		tmp = tmp->next;
	tab = (char **) malloc (sizeof(char *) * (i + 1));
	tmp = lst_env;
	i = 0;
	while (tmp)
	{
		char_tmp = ft_strjoin(tmp->var, "=");
		tab[i] = ft_strjoin(char_tmp, tmp->value); //check for leaks
		tmp = tmp->next;
        // free(char_tmp);
		i++;
	}
	tab[i] = NULL;
    i = -1;
    tmp = lst_env;
	while (tmp && tab[++i])
    {
        printf("%s=%s | %s\n", tmp->var, tmp->value, tab[i]);
		tmp = tmp->next;
    }
	return (tab);
}

int	ft_exec(char **data, char **av, t_env *lst_env)
{
	pid_t	c_pid;
	char	**env;

	env = list_to_tab(lst_env);
	if ((c_pid = fork()) == -1)
	{
		printf("here\n");
		ft_putstr_fd("error\n", 2);
		g_exit = 127;
	}
	else if (c_pid == 0)
	{
		if (execve(data[0], av, env) == -1)
		{
			printf("here2\n");
			ft_putstr_fd("error\n", 2);
			g_exit = 127;
		}
		g_exit = 0;
	}
	exit(g_exit);
	return (0);
}

int	ft_exec2(char **data, char **env)
{
	pid_t	c_pid;
    char    **av;
	//char	**env;

	//env = list_to_tab(lst_env);
    
	if ((c_pid = fork()) == -1)
	{
		printf("here\n");
		ft_putstr_fd("error\n", 2);
		g_exit = 127;
	}
	else if (c_pid == 0)
	{
		if (execve(data[0], av, env) == -1)
		{
			printf("here2\n");
			ft_putstr_fd("error\n", 2);
			g_exit = 127;
		}
		g_exit = 0;
	}
	exit(g_exit);
	return (0);
}
