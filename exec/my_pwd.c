/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:19:57 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/25 19:54:36 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int my_pwd(void)
{
    char    cwd[PATH_MAX];

    if (!getcwd(cwd, sizeof(cwd)))
        g_exit = 1; //verify
    printf("%s\n", cwd);
    return (0);
}