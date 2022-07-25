/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:21:01 by ilahyani          #+#    #+#             */
/*   Updated: 2021/11/20 11:57:10 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

static int	frontcheck(char *s1, char const *set)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (set[i])
	{
		if (set[i] == s1[j])
		{
			j++;
			i = -1;
		}
		i++;
	}
	return (j);
}

static int	backcheck(char *s1, char const *set)
{
	int		l;
	size_t	lens1;

	l = 0;
	lens1 = ft_strlen(s1);
	while (set[l])
	{
		if (set[l] == s1[lens1 - 1])
		{
			lens1--;
			l = -1;
		}
		l++;
	}
	return (lens1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		lens1;
	char	*s2;
	char	*s1cpy;

	if (!s1)
		return (0);
	s1cpy = (char *)s1;
	s1cpy += frontcheck(s1cpy, set);
	lens1 = backcheck(s1cpy, set);
	if (lens1 < 0)
		return (ft_strdup(""));
	s2 = (char *) malloc (lens1 + 1);
	if (!s2)
		return (0);
	i = 0;
	while (lens1--)
	{
		s2[i] = s1cpy[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
