/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:20:18 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/25 18:40:53 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int my_unset(t_env *env, char **data)
{
    t_env  *tmp;
    t_env  *tmp2;
    int     i;

    if (!data[1])
        return (1);
    i = 0;
    while (data[++i])
    {
        if (find_char(data[i], '=') || (data[i][0] >= '0' && data[i][0] <= '9'))
        {
            ft_putstr_fd("minishell: unset: ", 2);
            ft_putstr_fd(data[i], 2);
            ft_putstr_fd(": not a valid identifier\n", 2);
            //err_print()
            return (1);
        }
        tmp = env;
        while (tmp->next && ft_strcmp(tmp->next->var, data[i]))
            tmp = tmp->next;
        if (tmp->next)
        {
            tmp2 = tmp->next;
            tmp->next = tmp->next->next;
            free(tmp2);
        }
    }
    return (0);
}
