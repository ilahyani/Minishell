/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:20:18 by ilahyani          #+#    #+#             */
/*   Updated: 2022/06/26 12:20:34 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    my_unset(t_list *env, char **data)
{
    t_list  *tmp;
    t_list  *tmp2;
    int     i;

    i = 0;
    while (data[++i])
    {
        if (find_char(data[i], '=') || (data[i][0] >= '0' && data[i][0] <= '9'))
        {
            printf("minishell: unset: %s: not a valid identifier\n", data[i]);
            return ;
        }
        tmp = env;
        while (tmp->next && ft_strncmp(tmp->next->content, data[i], ft_strlen(data[i])))
            tmp = tmp->next;
        if (tmp->next)
        {
            tmp2 = tmp->next;
            tmp->next = tmp->next->next;
            free(tmp2);
        }
    }
}
