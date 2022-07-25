/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 18:58:25 by mjlem             #+#    #+#             */
/*   Updated: 2022/07/19 22:08:24 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	int		i;
	int		l;
	char	*k;
	int		j;

	if (!s2)
		return (NULL);
	if (!s1)
		s1 = ft_strdup("");
	i = ft_strlen(s1);
	l = ft_strlen(s2);
	k = (char *) malloc (i + l + 1);
	if (!k)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		k[j++] = s1[i++];
	l = 0;
	while (s2[l])
		k[j++] = s2[l++];
	k[j] = '\0';
	free (s1);
	return (k);
}
