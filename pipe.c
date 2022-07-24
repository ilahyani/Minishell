/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:53:48 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/24 12:46:54 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: heredoc dup bug - redir priority - sleep test

void    pipe_heredoc(char *data, t_env *lst_env, t_env *expand)
{
    char **data_tab = ft_split(data, '<');
    int j = -1;
    char *rdline_2;
    int tmpfd;
    
    while (data_tab[++j])
        data_tab[j] = ft_strtrim(data_tab[j], " "); //free
    tmpfd = open("tmpfile", O_CREAT | O_TRUNC | O_RDWR, 0777);
    while(1)
    {
        rdline_2 = readline("> ");
        if (!rdline_2 || !ft_strcmp(rdline_2, data_tab[1])) {
            break ;
        }
        if (rdline_2[0] == '$')
            print_fd(expand, lst_env, rdline_2, tmpfd);
        else
            ft_putendl_fd(rdline_2, tmpfd);
    }
    free(rdline_2);
    close (tmpfd);
    tmpfd = open("tmpfile", O_RDONLY);
    dup2(tmpfd, STDIN_FILENO);
    close(tmpfd);
    char **cmd_tab = ft_split(data_tab[0], ' ');
    check_cmd(cmd_tab, lst_env, expand);
    free_tab(cmd_tab);
    // unlink("tmpfile");
    // exec_child(data_tab[0], lst_env, expand);
    // char *cmd = ft_split(data_tab[0], ' ');
    // execve(get_path(cmd[0], lst_env), cmd, list_to_tab(lst_env));
}

int ft_pipe(char *line, t_env *lst_env, t_env *expand)
{
    char    **pipes;
    char    **cmd;
    int     cmd_num;
    int     fd[2];
    pid_t   c_pid;
    int     i;
    int     s_in;
    // int     s_out;
    int     tr_pipe = 0;
    char    *rdline;

    s_in = dup(0);
    // s_out = dup(1);
    pipes = ft_split(line, '|');
    cmd_num = sizeof_array(pipes);
    if (line[ft_strlen(line) - 1] == '|')
    {
        cmd_num++;
        tr_pipe = 1;
    }
    i = 0;
    while (i < cmd_num)
    {
        if (pipe(fd) == -1)
            return (1);
        c_pid = fork();
        if (c_pid == -1)
            return(ft_putstr_fd("error\n", 2), 1);
        else if (c_pid == 0)
        {
            if (find_char(pipes[i], '<') || find_char(pipes[i], '>'))
            {
                if (find_char(pipes[i], '<') && pipes[i][find_char(pipes[i], '<') + 1] == '<')
                {
                    dup2(s_in, STDIN_FILENO);
                    close(s_in);
                    pipe_heredoc(pipes[i], lst_env, expand);
                    if (i != cmd_num - 1)
                        dup2(fd[1], STDOUT_FILENO);
                    close(fd[1]);
                    // dup2(fd[0], STDIN_FILENO);
                    close(fd[0]);
                    g_exit = 0;
                    exit(0);
                }
                else {
                    close(fd[1]);
                    close(fd[0]);
                    redir_io(pipes[i], lst_env, expand);
                    g_exit = 0;
                    exit(0);
                }
            }
            else
            {
                if (i != cmd_num - 1)
                {
                    dup2(fd[1], STDOUT_FILENO);
                    close(fd[1]);
                    close(fd[0]);
                }
                cmd = ft_split(pipes[i], ' ');
                check_cmd(cmd, lst_env, expand);
                free_tab(cmd);
                g_exit = 0;
                exit(0);
            }
        }
        else
            wait(NULL);
        i++;
        if (i == cmd_num - 1 && tr_pipe == 1)
        {
            dup2(s_in, STDIN_FILENO);
            while (1)
            {
                rdline = readline("> ");
                if (!rdline)
                    return (err_print("syntax error", "unexpected end of file"), 258);
                if (ft_strcmp(rdline, ""))
                    break;
            }
            free(pipes[i]);
            pipes[i] = ft_strdup(rdline);
            free(rdline);
        }
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
    }
    dup2(s_in, STDIN_FILENO);
    close(s_in);
    return (0);
}
