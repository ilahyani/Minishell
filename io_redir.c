/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 22:39:06 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/19 23:45:31 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_heredoc(char *data, t_env *lst_env, t_env *expand);

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
        if (data[0][find_char(data[0], '<') + 1] == '<')
            ft_heredoc(data[0], lst_env, expand);
        else
            i_redir(data[0], lst_env, expand);
    }
    return (0); // 258 in case of failure
}

void    ft_heredoc(char *data, t_env *lst_env, t_env *expand)
{
    char    **data_tab;
    char    *line;
    int     fd[2];

    data_tab = ft_split(data, '<');
    pid_t c_pid = fork();
    if (c_pid == -1)
        ft_putstr_fd("errorY\n", 2);
    else if (c_pid == 0)
    {
        if (pipe(fd) == -1)
        {
            g_exit = 1;
            exit(1);
        }
        while(1)
        {
            line = readline("> ");
            if (!line || !ft_strcmp(line, data_tab[1]))
            {
                free(line);
                break;
            }
            ft_putendl_fd(line, fd[1]);
        }
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]); 
        exec_child(data_tab[0], lst_env, expand);
    }
    else 
        wait(NULL); 
}

void    i_redir(char *data, t_env *lst_env, t_env *expand)
{
    pid_t   c_pid;
    char    **data_tab;
    int     redirect_fd;

    data_tab = ft_split(data, '<');
    if (!data_tab)
    {
        ft_putendl_fd("errorX", 2);
        return ;
    }
    redirect_fd = open(data_tab[1], O_CREAT | O_RDONLY, S_IRWXU);
    c_pid = fork();
    if (c_pid == -1)
        ft_putstr_fd("errorY\n", 2);
    else if (c_pid == 0)
    {
        dup2(redirect_fd, STDIN_FILENO);
        close(redirect_fd);
        exec_child(data_tab[0], lst_env, expand);
    }
    else 
        wait(NULL);
    free_tab(data_tab);
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
    {
        dup2(redirect_fd, STDOUT_FILENO);
        close(redirect_fd);
        exec_child(data_tab[0], lst_env, expand);
    }
    else 
        wait(NULL);
    free_tab(data_tab);
}

void    exec_child(char *cmd, t_env *lst_env, t_env *expand)
{
    char *cmd_tab[2];

    cmd_tab[0] = cmd;
    cmd_tab[1] = NULL;
    check_cmd(cmd_tab, lst_env, expand);
    exit(g_exit);
}
