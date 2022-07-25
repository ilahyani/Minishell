/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 22:39:06 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/25 18:40:53 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//TODO: multiple redirct files:

//ex1: grep a < file1 < file2 < file3 < file4  =>  ignores all existing files and goes to 
//the last one unless a file before that doesnt exist (open(file) == -1)

//ex2: ls > a > b > c > d  =>  ignores all existing files and goes to the last one 
//unless a file before that doesnt exist (open(file) == -1)

int redir_io(char *line, t_env *lst_env, t_env *expand)
{
    if (find_char(line, '>'))
    {
        if (line[find_char(line, '>') + 1] == '>')
            o_redir(line, lst_env, expand, 1);
        else
            o_redir(line, lst_env, expand, 0);
    }
    else if (find_char(line, '<'))
    {
        if (line[find_char(line, '<') + 1] == '<')
            ft_heredoc(line, lst_env, expand);
        else
            i_redir(line, lst_env, expand);
    }
    return (0); // 258 in case of failure
}

void    print_fd(t_env *expand, t_env *lst_env, char *arg, int fd)
{
    t_env   *tmp;

    if (!ft_strcmp(arg, "$?")) {
        ft_putnbr_fd(g_exit, fd);
        ft_putchar_fd('\n', fd);
    }
    else
    {
        tmp = expand;
        while (tmp && ft_strcmp(tmp->var, arg + 1))
            tmp = tmp->next;
        if (tmp)
            ft_putendl_fd(tmp->value, fd);
        else
        {
            tmp = lst_env;
            while (tmp && ft_strcmp(tmp->var, arg + 1))
                tmp = tmp->next;
            if (tmp)
                ft_putendl_fd(tmp->value, fd);
            else
                ft_putstr_fd("\n", fd);
        }
    }
}

void    ft_heredoc(char *data, t_env *lst_env, t_env *expand)
{
    char    **data_tab;
    char    *line;
    pid_t   c_pid;
    int     i;
    int     fd[2];

    data_tab = ft_split(data, '<');
    i = -1;
    while (data_tab[++i])
        data_tab[i] = ft_strtrim(data_tab[i], " "); //free
    c_pid = fork();
    if (c_pid == -1)
        ft_putstr_fd("errorY\n", 2);
    else if (c_pid == 0)
    {
        if (pipe(fd) == -1)
        {
            g_exit = 1;
            exit(g_exit);
        }
        while(1)
        {
            line = readline("> ");
            if (!line || !ft_strcmp(line, data_tab[1]))
            {
                free(line);
                break;
            }
            if (line[0] == '$')
                print_fd(expand, lst_env, line, fd[1]);
            else
                ft_putendl_fd(line, fd[1]);
        }
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
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
    int     i;

    data_tab = ft_split(data, '<');
    i = -1;
    while (data_tab[++i])
        data_tab[i] = ft_strtrim(data_tab[i], " ");//free
    if (!data_tab)
    {
        ft_putendl_fd("errorX", 2);
        return ;
    }
    redirect_fd = open(data_tab[1], O_RDONLY, S_IRWXU);
    if (redirect_fd == -1)
    {
        err_print(data_tab[1], "No such file or directory");
        g_exit = 1;
        return ;
    }
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
    int     i;

    data_tab = ft_split(data, '>');
    if (!data_tab)
    {
        ft_putendl_fd("errorX", 2);
        return ;
    }
    i = -1;
    while (data_tab[++i])
        data_tab[i] = ft_strtrim(data_tab[i], " ");//free
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
    char **cmd_tab;

    cmd_tab = ft_split(cmd, ' ');
    check_cmd(cmd_tab, lst_env, expand);
    free_tab(cmd_tab);
    g_exit = 0;
    exit(0);
}
