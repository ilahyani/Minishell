/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:32:14 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/31 06:37:49 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int multi_redic_check(t_node *cmd)
{
    int i;

    if (!cmd)
        return (-1);
    i = 0;
    while (cmd && cmd->type != PIPE)
    {
        if (cmd->type == OUT_REDIR || cmd->type == IN_REDIR 
        || cmd->type == RE_ADD || cmd->type == HERE_DOC)
            i++;
        cmd = cmd->next;
    }
    return (i);
}

char    *check_file(t_node *node)
{
    if (node->type == WORD)
        return (node->next->cmd[0]);
    else
        return (node->cmd[0]);
}

void    data_init(t_redir *data)
{
    data->cmd = NULL;
    data->in_red = -11;
    data->out_red = -11;
    data->her_doc = NULL;
}

void    fd_reset(int fd[2])
{
    dup2(fd[0], STDIN_FILENO);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
}

void    print_fd(t_env *lst_env, char *arg, int fd)
{
    t_env   *tmp;

    if (!ft_strcmp(arg, "$?")) {
        ft_putnbr_fd(g_glob.status, fd);
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
