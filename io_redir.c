/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 22:39:06 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/15 00:40:00 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int redir_io(char **data, t_env *lst_env)
{
    if (find_char(data[0], '>'))
    {
        if (data[0][find_char(data[0], '>') + 1] == '>')
            o_redir_ap(data[0], lst_env);
        else
            printf("o_redir\n");
    }
    else if (find_char(data[0], '<'))
    {
        if (data[0][find_char(data[0], '>') + 1] == '<')
            printf("i_redir_app\n");
        else
            printf("i_redir\n");
    }
    return (0); // 258 in case of failure
}

void    o_redir_ap(char *data, t_env *lst_env)
{
    // pid_t   c_pid;
    char **data_tab;
    int redirect_fd;

    data_tab = ft_split(data, '>');
    redirect_fd = open(data_tab[1], O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
    dup2(redirect_fd, STDOUT_FILENO);
    // pid_t c_pid = fork();
    // if (c_pid == -1)
    //     ft_putstr_fd("->error\n", 2);
    // else if (c_pid == 0)
    // {
    //     check_cmd(&data_tab[0], lst_env, NULL);
    //     exit(g_exit);
    // }
    // else 
    //     wait(NULL);
    close(redirect_fd);
    check_cmd(&data_tab[0], lst_env, NULL);
    //free data_tab
}
