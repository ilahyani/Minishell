/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:45:52 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/09 21:04:09 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_print(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->var, tmp->value);
		else
			printf("declare -x %s\n", tmp->var);
		tmp = tmp->next;
	}
}

char	*ft_strldup(char *src, size_t len)
{
	int		i;
	char	*dst;

	if (!src)
		return (NULL);
	dst = (char *) malloc((len + 1) * sizeof(char));
	i = -1;
	while (++i < (int) len)
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

int	check_error(char *buff)
{
	char	**tab;
	int		i;

	if (!ft_isalpha(buff[0]) && buff[0] != '_')
		return (1);
	tab = ft_split(buff, '=');
	if (!tab)
		return (ft_putendl_fd("Unexpected error occured\n", 2), 0);
	if (find_char(tab[0], '+') && tab[0][find_char(tab[0], '+') + 1] != '\0')
		return (free_tab(tab), 1);
	i = 0;
	while (tab[0][++i])
		if (!ft_isalnum(tab[0][i]) && tab[0][i] != '_' && tab[0][i] != '+')
			return (free_tab(tab), 1);
	free_tab(tab);
	return (0);
}
