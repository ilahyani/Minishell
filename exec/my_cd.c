/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:17:12 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/28 13:31:32 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    update_env(t_env *env_list, char *env, char *val)
{
    t_env   *tmp;

    tmp = env_list;
    while (tmp && ft_strcmp(tmp->var, env))
        tmp = tmp->next;
    if (tmp)
        tmp->value = val;
    else
        env_lstadd_back(&env_list, env_lstnew(env, val));
        
}

int my_cd(t_env *lst_env, char **data)
{
    char    *path;
    char    *cwd;

    cwd = NULL;
    if(sizeof_array(data) == 1 || !ft_strcmp(data[1], "~"))
    {
        path = ft_getenv("HOME", lst_env);
        if(!path)
            return (ft_putstr_fd("HOME not set\n", 2), 1);
    }
    else if (!ft_strcmp(data[1], "-"))
    {
        path = ft_getenv("OLDPWD", lst_env);
        if(!path)
            return (ft_putstr_fd("OLDPWD not set\n", 2), 1);
        printf("%s\n", ft_getenv("OLDPWD", lst_env));
    }
    else if (!ft_strcmp(data[1], ".") && !getcwd(cwd, sizeof(cwd)))
    {
        free (cwd);
        return (ft_putstr_fd("minishell: cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2), 0);
    }
    else
        path = data[1];
    update_env(lst_env, "OLDPWD", getcwd(cwd, sizeof(cwd)));
    if (!getcwd(cwd, sizeof(cwd)))
        update_env(lst_env, "OLDPWD", ft_getenv("PWD", lst_env));
    if (chdir(path) != 0)
        return (ft_putstr_fd("minishell: cd: No such file or directory\n", 2), 1);
    update_env(lst_env, "PWD", getcwd(cwd, sizeof(cwd)));
    return (0);
}
