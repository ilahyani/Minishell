/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 22:39:06 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/30 18:41:00 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int redir_io(t_node *cmd, t_env *lst_env)
{
    if (multi_redic_check(cmd) == 1)
    {
        if (find_char_2(cmd, OUT_REDIR))
            o_redir(cmd, lst_env, 0);
        else if (find_char_2(cmd, RE_ADD))
            o_redir(cmd, lst_env, 1);
        else if (find_char_2(cmd, IN_REDIR)) 
            i_redir(cmd, lst_env);
        else if (find_char_2(cmd, HERE_DOC))
            ft_heredoc(cmd, lst_env);
        return (0);
    }
    return (redir_io_pro_max(cmd, lst_env));
}

/*    REDIRECT IO PRO MAX    */

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

void    data_init(t_redir *data)
{
    data->cmd = NULL;
    data->in_red = -11;
    data->out_red = -11;
    data->her_doc = NULL;
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

void    fd_reset(int fd[2])
{
    dup2(fd[0], STDIN_FILENO);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
}

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

/*    REDIRECT IO    */

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

char    *check_file(t_node *node)
{
    if (node->type == WORD)
        return (node->next->cmd[0]);
    else
        return (node->cmd[0]);
}

void    ft_heredoc(t_node *node, t_env *lst_env)
{
    char    *line;
    int     tmpfd;
    int     s_in;

    s_in = dup(0);
    tmpfd = open("tmpfile", O_CREAT | O_TRUNC | O_RDWR, 0777);
    while(1)
    {
        line = readline("> ");
        if (!line || !ft_strcmp(line, check_file(node)))
            break ;
        if (line[0] == '$')
            print_fd(lst_env, line, tmpfd);
        else
            ft_putendl_fd(line, tmpfd);
    }
    free(line);
    close(tmpfd);
    tmpfd = open("tmpfile", O_RDONLY);
    dup2(tmpfd, STDIN_FILENO);
    close(tmpfd);
    if (node->type == WORD)
        check_cmd(node->cmd, &lst_env);
    unlink("tmpfile");
    dup2(s_in, STDIN_FILENO);
    close(s_in);
}

void    i_redir(t_node *cmd, t_env *lst_env)
{
    pid_t   c_pid;
    int     redirect_fd;
    char    *file;

    file = check_file(cmd);
    redirect_fd = open(file, O_RDONLY, S_IRWXU);
    if (redirect_fd == -1)
    {
        err_print(file, "No such file or directory");
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
        if (cmd->type == WORD)
            check_cmd(cmd->cmd, &lst_env);
        exit(0);
    }
    close(redirect_fd);
    wait(NULL);
}

void    o_redir(t_node *cmd, t_env *lst_env, int append)
{
    pid_t   c_pid;
    int     redirect_fd;
    char    *file;

    file = check_file(cmd);
    if (append)
        redirect_fd = open(file, O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
    else
        redirect_fd = open(file, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
    if (redirect_fd == -1)
    {
        err_print(file, "Is a directory");
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
        dup2(redirect_fd, STDOUT_FILENO);
        close(redirect_fd);
        if (cmd->type == WORD)
            check_cmd(cmd->cmd, &lst_env);
        exit(0);
    }
    wait(NULL);
    close(redirect_fd);
}
