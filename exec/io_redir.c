/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 22:39:06 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/25 23:04:23 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//TODO: multiple redirct files:

//ex1: grep a < file1 < file2 < file3 < file4  =>  ignores all existing files and goes to 
//the last one unless a file before that doesnt exist (open(file) == -1)

//ex2: ls > a > b > c > d  =>  ignores all existing files and goes to the last one 
//unless a file before that doesnt exist (open(file) == -1)

int redir_io(t_node *cmd, t_env *lst_env)
{
    if (find_char_2(cmd, OUT_REDIR))
        o_redir(cmd, lst_env, 0);
    else if (find_char_2(cmd, RE_ADD))
        o_redir(cmd, lst_env, 1);
    else if (find_char_2(cmd, IN_REDIR)) 
        i_redir(cmd, lst_env);
    else if (find_char_2(cmd, HERE_DOC))
        ft_heredoc(cmd, lst_env);
    return (0); // 258 in case of failure
}

void    print_fd(t_env *lst_env, char *arg, int fd)
{
    t_env   *tmp;

    if (!ft_strcmp(arg, "$?")) {
        ft_putnbr_fd(g_exit, fd);
        ft_putchar_fd('\n', fd);
    }
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

void    ft_heredoc(t_node *cmd, t_env *lst_env)
{
    char    *line;
    pid_t   c_pid;
    int     fd[2];

    c_pid = fork();
    if (c_pid == -1)
    {
        ft_putstr_fd("fork error\n", 2);
        g_exit = 1;
        return ;
    }
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
            if (!line || !ft_strcmp(line, cmd->next->cmd[0]))
            {
                free(line);
                break;
            }
            if (line[0] == '$')
                print_fd(lst_env, line, fd[1]);
            else
                ft_putendl_fd(line, fd[1]);
        }
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);
        check_cmd(cmd->cmd, lst_env, NULL);
        g_exit = 0;
        exit(0);
    }
    wait(NULL); 
}

void    i_redir(t_node *cmd, t_env *lst_env)
{
    pid_t   c_pid;
    int     redirect_fd;

    redirect_fd = open(cmd->next->cmd[0], O_RDONLY, S_IRWXU);
    if (redirect_fd == -1)
    {
        err_print(cmd->next->cmd[0], "No such file or directory");
        g_exit = 1;
        return ;
    }
    c_pid = fork();
    if (c_pid == -1)
    {
        ft_putstr_fd("fork error\n", 2);
        g_exit = 1;
        return ;
    }
    else if (c_pid == 0)
    {
        dup2(redirect_fd, STDIN_FILENO);
        close(redirect_fd);
        check_cmd(cmd->cmd, lst_env, NULL);
        g_exit = 0;
        exit(0);
    }
    wait(NULL);
}

void    o_redir(t_node *cmd, t_env *lst_env, int append)
{
    pid_t   c_pid;
    int     redirect_fd;

    if (append)
        redirect_fd = open(cmd->next->cmd[0], O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
    else
        redirect_fd = open(cmd->next->cmd[0], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
    c_pid = fork();
    if (c_pid == -1)
    {
        ft_putstr_fd("fork error\n", 2);
        g_exit = 1;
        return ;
    }
    else if (c_pid == 0)
    {
        dup2(redirect_fd, STDOUT_FILENO);
        close(redirect_fd);
        check_cmd(cmd->cmd, lst_env, NULL);
        g_exit = 0;
        exit(0);
    }
    wait(NULL);
}
