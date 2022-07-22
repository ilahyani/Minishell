/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:53:48 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/21 20:46:15 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_redic(char *cmd)
{
    if (find_char(cmd, '<') || find_char(cmd, '>'))
        return (1);
    return (0);
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

    s_in = dup(0);
    pipes = ft_split(line, '|');
    cmd_num = sizeof_array(pipes);
    i = -1;
    while (++i < cmd_num)
    {
        if (pipe(fd) == -1)
            return (1);
        c_pid = fork();
        if (c_pid == -1)
            return(ft_putstr_fd("error\n", 2), 1);
        else if (c_pid == 0)
        {
            if (check_redic(pipes[i]))
                redir_io(pipes[i], lst_env, expand);
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
            // free cmd
            check_cmd(cmd, lst_env, expand);
            exit(0);
        }
        else
            wait(NULL);
	    dup2(fd[0], STDIN_FILENO);
	    close(fd[0]);
        close(fd[1]);
    }
    dup2(s_in, STDIN_FILENO);
    close(s_in);
    return (0);
}
