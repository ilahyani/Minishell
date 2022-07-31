/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redir_pro_max.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:29:30 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/31 06:33:53 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int redir_io_pro_max(t_node *cmd, t_env *lst_env)
{
    t_redir data;
    int     s_fd[2];
    struct  stat buf;

    s_fd[1] = dup(1);
    s_fd[0] = dup(0);
    if (!cmd)
        return (fd_reset(s_fd), 1);
    get_data(cmd, &data, lst_env);
    if (data.in_red == -1 || data.out_red == -1)
    {
        if (data.in_red == -1)
        {
            if (fstat(data.out_red, &buf) == -1)
                close(data.out_red);
            err_print(cmd->cmd[0], "No such file or directory");
        }
        else if (data.out_red == -1)
        {
            if (fstat(data.in_red, &buf) == -1)
                close(data.in_red);
            err_print(cmd->cmd[0], "Error openning file");
        }
        return (fd_reset(s_fd), 1);
    }
    if (data.in_red != -11)
    {
        dup2(data.in_red, STDIN_FILENO);
        close(data.in_red);
    }
    if (data.out_red != -11)
    {
        dup2(data.out_red, STDOUT_FILENO);
        close(data.out_red);
    }
    if (data.cmd)
        check_cmd(data.cmd, &lst_env);
    free_tab(data.cmd);
    return (fd_reset(s_fd), 0);
}

void    get_data(t_node *cmd, t_redir *data, t_env *lst_env)
{
    int     i;
    int     p_fd[2];
    char    *line;
    struct  stat buf;
    
    data_init(data);
    if (cmd->type == WORD)
    {
        data->cmd = (char **) malloc (sizeof(char *) * (sizeof_array(cmd->cmd) + 1));
        i = -1;
        while (cmd->cmd[++i])
            data->cmd[i] = ft_strdup(cmd->cmd[i]);
        data->cmd[i] = NULL;
        cmd = cmd->next;
    }
    while (cmd && cmd->type != PIPE)
    {
        if (cmd->type == OUT_REDIR)
        {
            if (fstat(data->out_red, &buf) == -1)
                close(data->out_red);
            data->out_red = open(cmd->cmd[0], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
        }
        else if (cmd->type == RE_ADD)
        {
            if (fstat(data->out_red, &buf) == -1)
                close(data->out_red);
            data->out_red = open(cmd->cmd[0], O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
        }
        else if (cmd->type == IN_REDIR)
        {
            if (fstat(data->in_red, &buf) == -1)
                close(data->in_red);
            data->in_red = open(cmd->cmd[0], O_RDONLY, S_IRWXU);
        }
        else if (cmd->type == HERE_DOC)
        {
            data->her_doc = cmd->cmd[0];
            if (pipe(p_fd) == -1)
            {
                ft_putendl_fd("Here_Doc error", 2);
                return ;
            }
            while(1)
            {
                line = readline("> ");
                if (!line || !ft_strcmp(line, data->her_doc))
                    break;
                if (line[0] == '$')
                    print_fd(lst_env, line, p_fd[1]);
                else
                    ft_putendl_fd(line, p_fd[1]);
            }
            free(line);
            if (fstat(data->in_red, &buf) == -1)
                close(data->in_red);
            if (data->in_red != -1)
                data->in_red = p_fd[0];
            close(p_fd[1]);
        }
        cmd = cmd->next;
    }
}
