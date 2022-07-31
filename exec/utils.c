/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:28:22 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/31 06:59:52 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	find_char_2(t_node *cmd, int type)
{
	if (!cmd)
		return (0);
	while (cmd)
	{
		if (cmd->type == type)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

void	err_print(char *cmd, char *buff)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": ", 2);
	ft_putendl_fd(buff, 2);
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}
