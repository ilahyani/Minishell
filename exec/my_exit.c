/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:18:35 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/09 17:12:39 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_exit(char **data)
{
	printf("exit\n");
	if (sizeof_array(data) == 1)
		g_status = 0;
	else if (sizeof_array(data) == 2)
	{
		if (is_int(data[1]))
			g_status = get_status(ft_atoi(data[1]));
		else
		{
			err_print(data[0], "numeric argument required");
			g_status = 255;
		}
	}
	else
	{
		if (is_int(data[1]))
		{
			err_print(data[0], "too many arguments");
			g_status = 0;
			return ;
		}
		err_print(data[0], "numeric argument required");
	}
	exit(g_status);
}

int	get_status(int arg)
{
	if (arg == 2147483647)
		return (255);
	else if (arg >= 0 && arg <= 255)
		return (arg);
	else
		return (arg % 256);
}
