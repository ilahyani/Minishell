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
	char	*tmp=NULL;
	int		i;
	int		j;
	int		z;

	sorted = (char **) malloc(sizeof(char *) * (sizeof(tab) + 1));
	i = -1;
	while (tab[++i])
	{
		sorted[i] = (char *) malloc(ft_strlen(tab[i]) + 1);
		z = ft_strlcpy(sorted[i], tab[i], ft_strlen(tab[i]) + 1);
		if (i == 5)
			printf("z = %d\ntab: |%s|\nsorted: |%s| | %lu\n", z, tab[i], sorted[i], ft_strlen(sorted[i]));
	}
	sorted[i + 1] = NULL;
	printf("---------------------\n");
	for (int j = 0; j < i; j++)
	{
        printf("|%s|\n", sorted[j]);
		if (j == 5)
			printf("-->%lu\n", sizeof(sorted[i]));
	}
    printf("---------------------\n");
	i = 0;
    while (sorted[i])
    {
		j = i + 1;
		//printf(">>>|%d -> %s|\n", i, sorted[i]);
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

size_t	find_char(char *s, char c)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s) + 1)
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (0);
}

void	env_print(char	*env)
{
	int	p;

	p = -1;
	printf("declare -x ");
    while (env[++p])
    {
        printf("%c", env[p]);
        if (env[p] == '=')
            printf("\"");
    }
    printf("\"\n");
}

size_t	ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (ft_strlen(src));
}
