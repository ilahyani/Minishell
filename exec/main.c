/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:28:26 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/25 18:40:53 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// > if put in the beginning makes the command not run and no err is displayed
//TODO: shell inception sig handling -> sigaction? let's go

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
            printf("\b   \b\bexit\n");
            g_exit = 0;
            exit(g_exit);
        }
        if (!ft_strcmp(line, ""))
           continue ;
        data = ft_split(line, ' ');
        if (!data)
            break ;
        if (find_char(data[0], '='))
            expand = check_expantion(data, lst_env, expand); //work with address
        else if (find_char(line, '|'))
            g_exit = ft_pipe(line, lst_env, expand);
        else if (find_char(line, '>') || find_char(line, '<'))
            g_exit = redir_io(line, lst_env, expand);
        else
            check_cmd(data, lst_env, expand);
        if (ft_strlen(line) > 0)
				add_history(line);
        //free data
    }
    free(line);
    printf("\b   \b\bexit\n");
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
    signal(SIGQUIT, SIG_IGN);
    env_init(env, &lst_env);
    ft_readline(lst_env, expand);
    return (g_exit);
}
