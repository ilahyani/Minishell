/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:28:26 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/01 17:17:01 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: 
//Tidy this shit up
//Tidy up main()

void    check_cmd(char **cmd, t_env *lst_env, t_env *expand)
{
    if (!ft_strcmp(cmd[0], "pwd"))
        g_exit = my_pwd();
    else if (!ft_strcmp(cmd[0], "cd"))
        g_exit = my_cd(lst_env, cmd);
    else if (!ft_strcmp(cmd[0], "echo"))
        g_exit = my_echo(cmd, lst_env, expand);
    else if (!ft_strcmp(cmd[0], "exit"))
        my_exit(cmd);
    else if (!ft_strcmp(cmd[0], "export"))
        g_exit = my_export(cmd, lst_env);
    else if (!ft_strcmp(cmd[0], "env"))
        my_env(lst_env);
    else if (!ft_strcmp(cmd[0], "unset"))
        g_exit = my_unset(lst_env, cmd);
    else
        g_exit = ft_exec(cmd, lst_env);
}

int check_arg(char **args)
{
    int i;

    i = -1;
    while (find_char(args[++i], '='));
    return (i);
}

void    add_node(char *buff, t_env *tmp)
{
    char    *key;
    char    *value;

    key = ft_strldup(buff, find_char(buff, '=')); //free
    if (ft_strlen(strchr_plus(buff, '=')) > 0)
    {
        value = ft_strdup(strchr_plus(buff, '=')); //free
        env_lstadd_back(&tmp, env_lstnew(key, value));
    }
    else
        env_lstadd_back(&tmp, env_lstnew(key, ""));
}

void    update_node(char *buff, t_env *expand)
{
    if (ft_strlen(strchr_plus(buff, '=')) > 0)
        expand->value = ft_strdup(strchr_plus(buff, '='));
    else
        expand->value = ft_strdup("");
}

t_env   *check_expantion(char **args, t_env *lst_env, t_env *expantion)
{
    // char    *key;
    // char    *value;
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
            {
                add_node(args[i], tmp);
                // key = ft_strldup(args[i], find_char(args[i], '=')); //free
                // if (ft_strlen(strchr_plus(args[i], '=')) > 0)
                // {
                //     value = ft_strdup(strchr_plus(args[i], '=')); //free
                //     env_lstadd_back(&expantion, env_lstnew(key, value));
                // }
                // else
                //     env_lstadd_back(&expantion, env_lstnew(key, ""));
            }
            else
            {
                update_node(args[i], tmp);
            //  if (ft_strlen(strchr_plus(args[i], '=')) > 0)
            //      tmp->value = ft_strdup(strchr_plus(args[i], '='));
            //  else
            //      tmp->value = ft_strdup("");
            }
        }
    }
    else
        check_cmd(args + check_arg(args), lst_env, expantion);
    return (expantion);
}

int main(int ac, char **av, char **env)
{
    char    *line;
    char    **data;
    t_env   *lst_env;
    t_env   *expand;

    (void)ac;
    (void)av;
    lst_env = NULL;
    expand = NULL;
    lst_env = env_init(env, lst_env);
    while (1)
    {
        line = readline("🐌🐌🐌 ~ ");
        if (!ft_strcmp(line, ""))
           continue ;
        data = ft_split(line, ' ');
        if (!data)
            return (0);
        if (find_char(data[0], '='))
            expand = check_expantion(data, lst_env, expand);
        else
            check_cmd(data, lst_env, expand);
        add_history(line);
        //free data
    }
    return (0);
}
