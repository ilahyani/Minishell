/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:17:12 by ilahyani          #+#    #+#             */
/*   Updated: 2022/06/26 12:18:26 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_getenv(char *env, t_list *env_list)
{
    t_list  *tmp;

    tmp = env_list;
    while (tmp && ft_strncmp(env, tmp->content, ft_strlen(env)))
        tmp = tmp->next;
    if (tmp)
        return (tmp->content + find_char(tmp->content, '=') + 1);
    return (NULL);
}

void    update_env(t_list *env_list, char *env, char *value)
{
    t_list  *tmp;

    tmp = env_list;
    while (tmp && ft_strncmp(env, tmp->content, ft_strlen(env)))
        tmp = tmp->next;
    // printf("--> |%s|\n", (char *) tmp->content);
    if (tmp)
        tmp->content = value;
    else
        ft_lstadd_back(&env_list, ft_lstnew(value));
    // printf("--> |%s|\n", (char *) tmp->content);
}

int my_cd(char **data, t_list *env)
{
    // t_list  *tmp;
    char    *old_pwd;
    char    pwd[PATH_MAX];

    getcwd(pwd, sizeof(pwd)); //is this better or get the cwd from the t_list PWD
    old_pwd = ft_strjoin("OLDPWD=", pwd);
    update_env(env, "OLDPWD", old_pwd);
    // tmp = env;
    // while (tmp->next && ft_strncmp(tmp->content, "OLDPWD", 6))
    //     tmp = tmp->next;
    // if (tmp->next)
    //     tmp->content = old_pwd;
    // else
    //     ft_lstadd_back(&env, ft_lstnew(old_pwd));
    if (sizeof_array(data) == 1)
    {
        if (chdir(ft_getenv("HOME", env)) != 0)
            printf("minishell: cd: HOME not set\n");
    }
    else
    {
        if (!ft_strcmp(data[1], "~"))
        {
            if (chdir(ft_getenv("HOME", env)) != 0)
                printf("minishell: cd: HOME not set\n");
        }
        else if (!ft_strcmp(data[1], "-"))
        {
            if (chdir(ft_getenv("OLDPWD", env)) != 0)
                printf("minishell: cd: OLDPWD not set\n");
        }
        else if (chdir(data[1]) != 0)
            printf("minishell: cd: No such file or directory\n");
    }
    return (0);
}
