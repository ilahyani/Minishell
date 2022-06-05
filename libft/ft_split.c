/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 01:06:17 by ilahyani          #+#    #+#             */
/*   Updated: 2021/11/17 18:29:42 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int	i;
	int	len;
	int	start;

	i = 0;
	len = 0;
	start = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (start == 0)
			{
				start = 1;
				len++;
			}
		}
		else if (s[i] == c)
			start = 0;
		i++;
	}
	return (len);
}

static void	ft_free(char **tab, int j)
{
	while (j--)
		free(tab[j]);
	free(tab);
}

static char	**ft_fill(int count, const char *s, char c, char **tab)
{
	int		i;
	int		j;
	size_t	size;

	i = 0;
	j = 0;
	while (j < count)
	{
		while (s[i] == c)
			i++;
		size = 0;
		while (s[i + size] && s[i + size] != c)
			size++;
		tab[j] = ft_substr(s, i, size);
		if (!tab[j])
		{
			ft_free(tab, j);
			return (NULL);
		}
		j++;
		i += size;
	}
	tab[j] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**tab;

	if (!s)
		return (NULL);
	count = ft_count(s, c);
	tab = (char **) malloc ((count + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	tab = ft_fill(count, s, c, tab);
	return (tab);
}
