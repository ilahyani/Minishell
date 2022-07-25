/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:28:49 by ilahyani          #+#    #+#             */
/*   Updated: 2021/11/13 11:46:39 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char				*p;
	size_t				i;

	p = (char *)s;
	i = 0;
	while (i < n)
	{
		if (p[i] == (char)c)
			return ((void *)(p + i));
		i++;
	}
	return (0);
}
