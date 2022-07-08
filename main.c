/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:28:26 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/08 17:01:11 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
        g_exit = my_env(lst_env, cmd);
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

t_env   *add_node(char *buff, t_env *expantion)
{
    char    *key;
    char    *value;
    key = ft_strldup(buff, find_char(buff, '=')); //free
    if (ft_strlen(strchr_plus(buff, '=')) > 0)
    {
        value = ft_strdup(strchr_plus(buff, '=')); //free
        env_lstadd_back(&expantion, env_lstnew(key, value));
    }
    else
        env_lstadd_back(&expantion, env_lstnew(key, ""));
    printf("var1 = %s\n",expantion->var);
    printf("value1 = %s\n",expantion->value);
    return expantion;
}

t_env   *update_node(char *buff, t_env *expantion)
{
    if (ft_strlen(strchr_plus(buff, '=')) > 0)
        expantion->value = ft_strdup(strchr_plus(buff, '='));
    else
        expantion->value = ft_strdup("");
    return (expantion);
}

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
                expantion = add_node(args[i], expantion);
            else
                expantion = update_node(args[i], expantion);
        }
    }
    else
        check_cmd(args + check_arg(args), lst_env, expantion);
    return (expantion);
}

void    handler(int signum)
{
    if (signum == SIGINT)
    {
        write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
    }
    else if (signum == SIGQUIT)
        return ;
}

void    ft_readline(t_env *lst_env, t_env *expand)
{
    char    **data;
    char    *line;

    while (1)
    {
        line = readline("🐌🐌🐌 ~ ");
        if (!line)
        {
            g_exit = 0;
            printf("exit\n");
            exit(g_exit);
        }
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
}

int main(int ac, char **av, char **env)
{
    t_env   *lst_env;
    t_env   *expand;

    (void)ac;
    (void)av;
    lst_env = NULL;
    expand = NULL;
    signal(SIGINT, handler);
    signal(SIGQUIT, handler);
    lst_env = env_init(env, lst_env);
    ft_readline(lst_env, expand);
    return (0);
}
