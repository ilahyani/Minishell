/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:18:02 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/13 23:22:32 by ilahyani         ###   ########.fr       */
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

void    print_arg(t_env *expand, t_env *lst_env, char *arg)
{
    t_env   *tmp;

    tmp = expand;
    while (tmp && ft_strcmp(tmp->var, arg))
        tmp = tmp->next;
    if (tmp)
        printf("%s", tmp->value);
    else
    {
        tmp = lst_env;
        while (tmp && ft_strcmp(tmp->var, arg))
            tmp = tmp->next;
        if (tmp)
            printf("%s", tmp->value);
    }
}

void    ft_print(char *str, t_env *lst_env, t_env *expand)
{
    if (str[0] == '$')
    {
        if (!ft_strcmp(str, "$?"))
            printf("%d", g_exit);
        //check redir
        else
            print_arg(expand, lst_env, str + 1);
    }
    else
        printf("%s", str);
}

int my_echo(char **data, t_env *lst_env, t_env *expand)
{
    int i;
    int args;
    int new_line;

    args = sizeof_array(data);
    if (args == 1)
        return (printf("\n"), 0);
    i = 0;
    new_line = 0;
    while (flag_check(data[++i]) == 1);
    if (i > 1)
        new_line = 1;
    while (data[i])
    {
        ft_print(data[i], lst_env, expand);
        if (i++ != args - 1)
            printf(" ");
    }
    if (!new_line)
        printf("\n");
    return (0);
}
