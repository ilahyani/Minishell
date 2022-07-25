/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:19:57 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/25 18:40:53 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int my_pwd(void)
{
    char    cwd[PATH_MAX];

    if (!getcwd(cwd, sizeof(cwd)))
        g_exit = 1; //verify
    printf("%s\n", cwd);
    return (0);
}
