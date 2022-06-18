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
        return (2);
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
            perror("minishell: cd: ");
    }
    else if (chdir(data[1]) != 0)
        perror("minishell: cd: ");
    return (0);
}

void    my_exit(char **data)
{
    if (sizeof_array(data)  == 1)
        exit(1);
    else
    {
        if (is_int(data[1]) && data[2])
            printf("too many arguments\n");
        else
            exit(1);
    }
}

int my_export(char **data, char **env)
{
    char    **sorted_env;
    int     args;
    int     i;

    args = sizeof_array(data);
    sorted_env = sort_tab(env); // FREE THIS SHIT BEFORE EXIT;
    // for (i = 0; env[i]; i++)
    //     printf("|%s|\n", env[i]);
    // printf("---------------------\n");
    // for (i = 0; sorted_env[i]; i++)
    //     printf("|%s|\n", sorted_env[i]);
    // printf("---------------------\n");
    if (args == 1)
    {
        i = -1;
        while (sorted_env[++i])
            env_print(sorted_env[i]);
    }
    else
    {
        i = 0;
        while (env[i] && ft_strncmp(env[i], data[1], find_char(env[i], '=')))
            i++;
        if (env[i])
            env[i] = data[1];
        // else
        //     return (1);
    }
    return (0);
}

// Export x; x->export
// Export a=asdf; x->(env-malloc, export)
// Export +=