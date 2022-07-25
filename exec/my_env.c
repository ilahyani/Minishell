/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:18:52 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/25 19:54:16 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
