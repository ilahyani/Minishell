/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:28:26 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/14 22:21:49 by ilahyani         ###   ########.fr       */
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
    else if (!ft_strcmp(cmd[0], "export"))
        g_exit = my_export(cmd, lst_env);
    else if (!ft_strcmp(cmd[0], "env"))
        g_exit = my_env(lst_env, cmd);
    else if (!ft_strcmp(cmd[0], "unset"))
        g_exit = my_unset(lst_env, cmd);
    else if (!ft_strcmp(cmd[0], "exit"))
        my_exit(cmd);
    else
        g_exit = ft_exec(cmd, lst_env);
}

void    ft_readline(t_env *lst_env, t_env *expand)
{
    char    **data;
    char    *line;

    while (1)
    {
        line = readline("🐌🐌🐌 ~> ");
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
            break ;
        if (find_char(data[0], '='))
            expand = check_expantion(data, lst_env, expand); //work with address
        else if (find_char(data[0], '>') || find_char(data[0], '<'))
            g_exit = redir_io(data, lst_env);
        else
            check_cmd(data, lst_env, expand);
        if (ft_strlen(line) > 0)
				add_history(line);
        //free data
    }
    printf("\b   \b\bexit\n");
}

// > if put in the beginning makes the command not run and no err is displayed

int main(int ac, char **av, char **env)
{
    t_env   *lst_env;
    t_env   *expand;

    (void)ac;
    (void)av;
    lst_env = NULL;
    expand = NULL;
    signal(SIGINT, handler);
    signal(SIGQUIT, SIG_IGN);
    env_init(env, &lst_env);
    ft_readline(lst_env, expand);
    return (g_exit);
}
