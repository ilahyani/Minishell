/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 22:39:06 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/15 11:39:35 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int redir_io(char **data, t_env *lst_env, t_env *expand)
{
    if (find_char(data[0], '>'))
    {
        if (data[0][find_char(data[0], '>') + 1] == '>')
            o_redir(data[0], lst_env, expand, 1);
        else
            o_redir(data[0], lst_env, expand, 0);
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

void    o_redir(char *data, t_env *lst_env, t_env *expand, int append)
{
    pid_t   c_pid;
    char    **data_tab;
    int     redirect_fd;

    data_tab = ft_split(data, '>');
    if (!data_tab)
    {
        ft_putendl_fd("errorX", 2);
        return ;
    }
    if (append)
        redirect_fd = open(data_tab[1], O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
    else
        redirect_fd = open(data_tab[1], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
    c_pid = fork();
    if (c_pid == -1)
        ft_putstr_fd("errorY\n", 2);
    else if (c_pid == 0)
        exec_child(redirect_fd, data_tab[0], lst_env, expand);
    else 
        wait(NULL);
    free_tab(data_tab);
}

void    exec_child(int redirect_fd, char *cmd, t_env *lst_env, t_env *expand)
{
    char *cmd_tab[2];

    dup2(redirect_fd, STDOUT_FILENO);
    close(redirect_fd);
    cmd_tab[0] = cmd;
    cmd_tab[1] = NULL;
    check_cmd(cmd_tab, lst_env, expand);
    exit(g_exit);
}
