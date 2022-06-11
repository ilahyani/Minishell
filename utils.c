/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:28:22 by ilahyani          #+#    #+#             */
/*   Updated: 2022/06/07 13:42:48 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
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
	while (c[++i])
		if (c[i] < '0' || c[i] > '9')
			return (0);
	return (1);
}

char	**parser(char *line)
{
	char **data;

	if (!line)
		return (0);
	data = ft_split(line, ' ');
	return (data);
}

int	ft_exec(char **data)
{
	// char	*path;
	// char	**path_grp;
	pid_t	f;
	char	*av[2]={"ls", NULL};

	// path = getenv("PATH");
	// path_grp = ft_split(path, ":");
	//join data[0] with each path_grp[i] till you get the right one;
	f = fork();
	if (f == 0)
		execve(data[0], av, NULL);
	return (0);
}