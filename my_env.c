/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:18:52 by ilahyani          #+#    #+#             */
/*   Updated: 2022/06/27 12:37:55 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    my_env(t_env *env)
{
    t_env  *tmp;

    tmp = env;
    while (tmp)
    {
        if (tmp->value)
            printf("%s=%s\n", (char *)tmp->var, (char *)tmp->value);
        tmp = tmp->next;
    }
}
