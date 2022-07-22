/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:53:48 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/22 06:35:56 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: redir dup bug

int ft_pipe(char *line, t_env *lst_env, t_env *expand)
{
    char    **pipes;
    char    **cmd;
    int     cmd_num;
    int     fd[2];
    pid_t   c_pid;
    int     i;
    int     s_in;
    int     tr_pipe = 0;
    char    *rdline;

    s_in = dup(0);
    pipes = ft_split(line, '|');
    cmd_num = sizeof_array(pipes);
    if (line[ft_strlen(line) - 1] == '|')
    {
        cmd_num++;
        tr_pipe = 1;
    }
    // printf(">%d\n", cmd_num);
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
                close(fd[0]);
                close(fd[1]);
                dup2(s_in, STDIN_FILENO);
                redir_io(pipes[i], lst_env, expand);
            }
            else
            {
                cmd = ft_split(pipes[i], ' ');
                if (i == 0)
                {
                    dup2(fd[1], STDOUT_FILENO);
                    close(fd[1]);
                    close(fd[0]);
                }
                else if (i != cmd_num - 1)
                {
                    dup2(fd[1], STDOUT_FILENO);
                    close(fd[1]);
                }
                check_cmd(cmd, lst_env, expand);
                // free cmd
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
                else if (ft_strcmp(rdline, ""))
                {
                    pipes[i] = rdline;
                    free(rdline);
                    break;
                }
            }
        }
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
    }
    dup2(s_in, STDIN_FILENO);
    close(s_in);
    return (0);
}
