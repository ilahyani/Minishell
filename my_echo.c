/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:18:02 by ilahyani          #+#    #+#             */
/*   Updated: 2022/06/30 21:32:48 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int flag_check(char *arg)
{
    int indx;

    if (!ft_strncmp(arg, "-n", 2))
    {
        indx = 2;
        while (arg[indx] && arg[indx] == 'n')
            indx++;
        if (!arg[indx])
            return (1);
    }
    return (0);
}

void    ft_print(char *str)
{
    if (!ft_strcmp(str, "$?"))
        printf("%d\n", g_exit);
    else
        printf("%s", str);
}

int my_echo(char **data)
{
    int i;
    int args;
    int new_line;

    args = sizeof_array(data);
    if (args == 1)
        return (printf("\n"), 0);
    i = 0;
    while (flag_check(data[++i]) == 1);
    if (i > 1)
        new_line = 1;
    while (data[i])
    {
        ft_print(data[i]);
        if (i++ != args - 1)
            printf(" ");
    }
    if (!new_line)
        printf("\n");
    return (0);
}
