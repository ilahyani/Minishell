/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:53:48 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/28 02:06:14 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int multi_pipe_check(t_node *cmd)
{
    int i;

    if (!cmd)
        return (-1);
    i = 0;
    while (cmd)
    {
        if (cmd->type == PIPE)
            i++;
        cmd = cmd->next;
    }
    return (i);
}

int check_redir(t_node *node)
{
    if (node->type == WORD)
        node = node->next;
    if (node && (node->type == HERE_DOC || node->type == IN_REDIR || node->type == OUT_REDIR || node->type == RE_ADD))
        return (1);
    return (0);
}

int check_heredoc(t_node *node)
{
    while (node && node->type != PIPE)
    {
        if (node->type == HERE_DOC)
            return (1);
        node = node->next;
    }
    return (0);
}

int is_last(t_node *node)
{
    if (!(node->next))
        return (1);
    while (check_redir(node))
        node = node->next;
    if (!node)
        return (1);
    return (0);
}

void    exec_child(t_node *node, t_env *lst_env, int fd[2], int s_in)
{
    if (check_redir(node))
    {
        close(fd[1]);
        close(fd[0]);
        if (check_heredoc(node))
            dup2(s_in, STDIN_FILENO);
        redir_io(node, lst_env);
    }
    else
    {
        if (!is_last(node))
            dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        close(fd[0]);
        check_cmd(node->cmd, lst_env);

    }
    exit(g_exit);
}

void    next_cmd(t_node **node)
{
    (* node) = (* node)->next;
    while (*node && check_redir(* node))
        *node = (* node)->next;
    if (*node && (* node)->type == PIPE)
        *node = (* node)->next;
}

void    s_in_reset(int s_in)
{
    dup2(s_in, STDIN_FILENO);
    close(s_in);
}

void    set_status(int j)
{
    int status;

    while (j--)
    {
        wait(&status);
        printf("->%d\n", WEXITSTATUS(status));
    }
    g_exit = WEXITSTATUS(status);
}

int ft_pipe(t_node *node, t_env *lst_env)
{
    int     fd[2];
    pid_t   c_pid;
    int     s_in;
    int     j;
    
    s_in = dup(0);
    j = 0;
    while (node)
    {
        j++;
        if (pipe(fd) == -1)
            return (1);
        c_pid = fork();
        if (c_pid == -1)
            return(ft_putstr_fd("fork error\n", 2), 1);
        else if (c_pid == 0)
            exec_child(node, lst_env, fd, s_in);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        next_cmd(&node);
    }
    set_status(j);
    return (s_in_reset(s_in), g_exit);
}
