/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:23:14 by ilahyani          #+#    #+#             */
/*   Updated: 2021/11/13 14:12:07 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *niddle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*b;
	char	*l;

	b = (char *) haystack;
	l = (char *) niddle;
	if (!*l)
		return ((char *)haystack);
	i = 0;
	while (b[i] && i < len)
	{
		j = 0;
		if (b[i] == l[j])
		{
			while (b[i + j] && i + j < len && b[i + j] == l[j])
				j++;
			if (l[j] == '\0')
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
