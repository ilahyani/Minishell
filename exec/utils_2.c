/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:58:54 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/07 16:05:53 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	sizeof_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		;
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

char	*ft_getenv(char *env, t_env *env_list)
{
	while (env_list && ft_strcmp(env, env_list->var))
		env_list = env_list->next;
	if (env_list)
		return (env_list->value);
	return (NULL);
}

int	event(void)
{
	return (0);
}
