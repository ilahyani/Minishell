/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:57:16 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/13 23:31:41 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env   *check_expantion(char **args, t_env *lst_env, t_env *expantion)
{
    t_env   *tmp;
    int     i;

    if (check_arg(args) == sizeof_array(args))
    {
        i = -1;
        while (args[++i])
        {
            tmp = expantion;
            while (tmp && ft_strcmp(tmp->var, ft_strldup(args[i], find_char(args[i], '='))))
                tmp = tmp->next;
            if (!tmp)
                add_node(args[i], &expantion);
            else
                update_node(args[i], &tmp);
        }
    }
    else
        check_cmd(args + check_arg(args), lst_env, expantion);
    return (expantion);
}

int check_arg(char **args)
{
    int i;

    i = -1;
    while (find_char(args[++i], '='));
    return (i);
}

void    add_node(char *buff, t_env **expantion)
{
    char    *key;
    char    *value;

    key = ft_strldup(buff, find_char(buff, '=')); //free
    if (ft_strlen(strchr_plus(buff, '=')) > 0)
    {
        value = ft_strdup(strchr_plus(buff, '=')); //free
        env_lstadd_back(expantion, env_lstnew(key, value));
    }
    else
        env_lstadd_back(expantion, env_lstnew(key, ""));
}

void    update_node(char *buff, t_env **expantion)
{
    if (ft_strlen(strchr_plus(buff, '=')) > 0)
        (*expantion)->value = ft_strdup(strchr_plus(buff, '='));
    else
        (*expantion)->value = ft_strdup("");
}
