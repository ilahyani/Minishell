/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:06:17 by ilahyani          #+#    #+#             */
/*   Updated: 2021/11/09 11:33:45 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*x1;
	const unsigned char	*x2;

	x1 = s1;
	x2 = s2;
	i = 0;
	if (n != 0)
	{
		while (x1[i] == x2[i] && i < n - 1)
			i++;
		return (x1[i] - x2[i]);
	}
	return (0);
}
