/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:28:30 by ilahyani          #+#    #+#             */
/*   Updated: 2022/06/18 12:59:13 by ilahyani         ###   ########.fr       */
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
            printf("minishell: cd: HOME not set\n");
    }
    else if (chdir(data[1]) != 0)
        printf("minishell: cd: No such file or directory\n");
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

void    my_env(char **env)
{
    int i;

    i = -1;
    while (env[++i])
        if (find_char(env[i], '=') != -1 && env[find_char(env[i], '=') + 1])
            printf("%s\n", env[i]);
}

void    my_unset(char **env, char **data)
{
    int i;
    int j;

    i = 1;
    while (data[i])
    {
        j = 0;
        // printf("%lu\n", ft_strlen(data[i]));
        while (env[j] && ft_strncmp(env[j], data[i], ft_strlen(data[i])))
            j++;
        // printf("|%s|\n", env[j]);
        if (env[j])
        {
            free(env[j]);
        }
        i++;
    }
}
