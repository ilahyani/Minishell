/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:19:30 by ilahyani          #+#    #+#             */
/*   Updated: 2022/06/26 12:19:45 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int my_export(char **data, char **env)
{
    char    **sorted;
    int     i;
    int     j;

    sorted = sort_tab(env);
    if (sizeof_array(data) == 1)
    {
        i = -1;
        while (sorted[++i])
        {
            if (!find_char(sorted[i], '='))
                printf("declare -x %s\n", sorted[i]);
            else
                env_print(sorted[i]);
        }
    }
    else
    {
        j = 0;
        while (data[++j])
        {
            i = 0;
            while (env[i] && ft_strncmp(env[i], data[j], find_char(env[i], '=')))
                i++;
            if (env[i] && !find_char(data[j], '='))
                continue ;
            if (env[i])
            {
                if (data[j][find_char(data[j], '=') - 1] == '+')
                    env[i] = ft_strjoin(env[i], data[j] + find_char(data[j], '=') + 1);
                else
                    env[i] = data[j];
            }
            else
            {
                i = -1;
                while(env[++i]);
                env[i] = ft_strdup(data[j]);
                env[i + 1] = NULL;
            }
        }
    }
    //FREE sorted
    return (0);
}
