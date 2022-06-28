/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:28:22 by ilahyani          #+#    #+#             */
/*   Updated: 2022/06/28 16:29:18 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	f;
	char	*av[2]={"ls", NULL};

	// path = getenv("PATH");
	// path_grp = ft_split(path, ":");
	//join data[0] with each path_grp[i] till you get the right one;
	f = fork();
	if (f == 0)
		execve(data[0], av, NULL);
	return (0);
}

char	**sort_tab(char **tab)
{
	char	**sorted;
	char	*tmp;
	int		i;
	int		j;

	sorted = (char **) malloc(sizeof(char *) * (sizeof_array(tab) + 1));
	i = -1;
	while (tab[++i])
		sorted[i] = ft_strdup(tab[i]);
	sorted[i] = NULL;
	i = 0;
    while (sorted[i])
    {
		j = i + 1;
        while (sorted[j])
        {
            if (ft_strcmp(sorted[i], sorted[j]) > 0)
            {
				tmp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = tmp;
            }
            j++;
        }
        i++;
    }
	return (sorted);
}

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

void	env_print(void	*env)
{
	int	p;
	char	*str;

	p = -1;
	str = env;
	printf("declare -x ");
    while (str[++p])
    {
        printf("%c", str[p]);
        if (str[p] == '=')
            printf("\"");
    }
    printf("\"\n");
}
