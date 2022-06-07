/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:28:30 by ilahyani          #+#    #+#             */
/*   Updated: 2022/06/07 14:58:51 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int my_echo(char **data)
{
    int i;
    int args;
    int new_line;

    args = sizeof_array(data);
    if (args == 1)
    {
        printf("\n");
        return (0);
    }
    i = 1;
    if (!ft_strcmp(data[1], "-n"))
    {
        new_line = 0;
        i++;
    }
    while (i < args)
    {
        printf("%s", data[i]);
        if (i++ != args - 1)
            printf(" ");
    }
    if (new_line)
        printf("\n");
    return (0);
}

int my_pwd(char **data)
{
    char    *cwd;
    int     args;

    args = sizeof_array(data);
    if (args > 1)
    {
        printf("too many arguments\n");
        return (0);
    }
    cwd = NULL;
    cwd = getcwd(cwd, 1000);
    if (!cwd)
        printf("error\n");
    printf("%s\n", cwd);
    return (0);
}


int my_cd(char **data)
{
    int args;

    args = sizeof_array(data);
    if (args == 1)
    {
        if (chdir(getenv("HOME")) != 0)
            printf("No such file or directory\n");
    }
    else if (chdir(data[1]) != 0)
        printf("No such file or directory\n");
    return (0);
}
