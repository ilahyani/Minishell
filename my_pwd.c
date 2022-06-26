/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:19:57 by ilahyani          #+#    #+#             */
/*   Updated: 2022/06/26 12:20:08 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int my_pwd(void)
{
    char    cwd[PATH_MAX];

    if (!getcwd(cwd, sizeof(cwd)))
    {
        printf("minishell: pwd: error\n");
        return (1);
    }
    else
        printf("%s\n", cwd);
    return (0);
}
