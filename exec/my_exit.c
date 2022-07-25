/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:18:35 by ilahyani          #+#    #+#             */
/*   Updated: 2022/06/30 12:52:16 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    my_exit(char **data)
{
    int size;
    int arg;

    printf("exit\n");
    size = sizeof_array(data);
    if (size == 1)
        g_exit = 0;
    else if (size == 2)
    {
        arg = ft_atoi(data[1]);
        if (is_int(data[1]))
        {
            if (arg == 2147483647)
                g_exit = 255;
            else if (arg >= 0)
                g_exit = arg;
            else
            {
                if ((arg * -1) % 256 == 0)
                {
                    printf("->0\n");
                    g_exit = 0;
                }
                else
                    g_exit = 256 * (1 + (-1 * arg)/256) + arg;
            }
        }
        else
        {
            ft_putstr_fd("minishell: exit: ", 2);
            ft_putstr_fd(data[1], 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            g_exit = 255;
        }
    }
    else
    {
        ft_putstr_fd("minisehll: exit: too many arguments\n", 2);
        g_exit = 0;
    }
    exit(g_exit);
}
