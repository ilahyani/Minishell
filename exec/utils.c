/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:28:22 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/25 21:57:47 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	sizeof_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i]);
	return (i);
}

int	is_int(char *c)
{
	int	i;

	i = -1;
	if (c[0] == '-' || c[0] == '+')
		i++;
	while (c[++i])
		if (c[i] < '0' || c[i] > '9')
			return (0);
	return (1);
}

// char	**parser(char *line)
// {
// 	char **data;

// 	if (!line)
// 		return (0);
// 	data = ft_split(line, ' ');
// 	return (data);
// }

char	*strchr_plus(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s) + 1)
	{
		if (s[i] == (char)c)
			return ((char *)(s + (i + 1)));
		i++;
	}
	return (0);
}

int	find_char(char *s, char c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (i < (int)ft_strlen(s) + 1)
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (0);
}

// int	find_char(t_node *cmd, int type)
// {
// 	if (!cmd)
// 		return (0);
// 	while (cmd)
// 	{
// 		if (cmd->type == type)
// 			return (1);
// 		cmd = cmd->next;
// 	}
// 	return (0);
// }

void	err_print(char *cmd, char *buff)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": ", 2);
	ft_putendl_fd(buff, 2);
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

char    *ft_getenv(char *env, t_env *env_list)
{
    while (env_list && ft_strcmp(env, env_list->var))
        env_list = env_list->next;
    if (env_list)
        return (env_list->value);
    return (NULL);
}
