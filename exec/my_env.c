/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:18:52 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/25 18:40:53 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int my_env(t_env *env, char **data)
{
    t_env  *tmp;

    if (sizeof_array(data) > 1)
    {
        ft_putstr_fd("env: ", 2);
        ft_putstr_fd(data[0], 2);
        ft_putstr_fd(": No such file or directory\n", 2);
    	return (127);
    }
    tmp = env;
    while (tmp)
    {
        if (tmp->value)
            printf("%s=%s\n", (char *)tmp->var, (char *)tmp->value);
        tmp = tmp->next;
    }
    return (0);
}
