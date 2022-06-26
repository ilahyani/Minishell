/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:18:52 by ilahyani          #+#    #+#             */
/*   Updated: 2022/06/26 12:19:14 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    my_env(t_list *env)
{
    t_list  *tmp;

    tmp = env;
    while (tmp->next)
    {
        if (tmp->content && find_char(tmp->content, '='))
            printf("%s\n", (char *)tmp->content);
        tmp = tmp->next;
    }
}
