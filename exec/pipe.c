/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:53:48 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/28 00:33:12 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//TODO: re-factor

void    pipe_heredoc(char *delmtr, t_env *lst_env)
{
    char    *rdline;
    int     tmpfd;
    
    tmpfd = open("tmpfile", O_CREAT | O_TRUNC | O_RDWR, 0777);
    while(1)
    {
        rdline = readline("> ");
        if (!rdline || !ft_strcmp(rdline, delmtr))
            break ;
        if (rdline[0] == '$')
            print_fd(lst_env, rdline, tmpfd);
        else
            ft_putendl_fd(rdline, tmpfd);
    }
    free(rdline);
    close(tmpfd);
    tmpfd = open("tmpfile", O_RDONLY);
    dup2(tmpfd, STDIN_FILENO);
    close(tmpfd);
}

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

void	print_list3(t_node *tokens)
{
	t_node	*tmp;
	int		i;

	tmp = tokens;
	i = 0;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
			printf("|%s|", tmp->cmd[i++]);
		printf("--%c\n", tmp->type);
		tmp = tmp->next;
	}
}

int check_redir(t_node *node)
{
    if (node->next && (node->next->type == HERE_DOC || node->next->type == IN_REDIR 
        || node->next->type == OUT_REDIR || node->next->type == RE_ADD))
        return (1);
    return (0);
}

// void    exec_child(t_node *node, t_env *lst_env, int fd[2], int cmd_num)
// {
//     if (check_redir(node))
//     {
//         close(fd[0]);
//         close(fd[1]);
//         if (node->next->type == HERE_DOC)
//             dup2(s_in, STDIN_FILENO);
//         redir_io(node, lst_env);
//         // if (node->next->type == HERE_DOC)
//         // {
//         //     ft_putendl_fd("here_dick", 2);
//         //     dup2(s_in, STDIN_FILENO);
//         //     close(s_in);
//         //     pipe_heredoc(node->next->cmd[0], lst_env);
//         //     check_cmd(node->cmd, lst_env);
//         //     unlink("tmpfile");
//         // }
//         // else 
//         // {
//         //     // close(fd[1]);
//         //     redir_io(node, lst_env);
//         // }
//     }
//     else
//     {
//         if (cmd_num > 1) //not last cmd
//             dup2(fd[1], STDOUT_FILENO);
//         close(fd[1]);
//         close(fd[0]);
//         check_cmd(node->cmd, lst_env);
//     }
//     exit(g_exit);
// }

int ft_pipe(t_node *node, t_env *lst_env)
{
    int     cmd_num;
    int     fd[2];
    pid_t   c_pid;
    int     s_in;
    
    s_in = dup(0);
    cmd_num = multi_pipe_check(node) + 1;
    while (node)
    {
        if (pipe(fd) == -1)
            return (1);
        c_pid = fork();
        if (c_pid == -1)
            return(ft_putstr_fd("fork error\n", 2), 1);
        else if (c_pid == 0)
        {
            // exec_child(node, lst_env, fd, cmd_num);
            if (check_redir(node))
            {
                close(fd[0]);
                close(fd[1]);
                if (node->next->type == HERE_DOC)
                    dup2(s_in, STDIN_FILENO);
                redir_io(node, lst_env);
                // if (node->next->type == HERE_DOC)
                // {
                //     ft_putendl_fd("here_dick", 2);
                //     dup2(s_in, STDIN_FILENO);
                //     close(s_in);
                //     pipe_heredoc(node->next->cmd[0], lst_env);
                //     check_cmd(node->cmd, lst_env);
                //     unlink("tmpfile");
                // }
                // else 
                // {
                //     // close(fd[1]);
                //     redir_io(node, lst_env);
                // }
            }
            else
            {
                if (cmd_num > 1) //not last cmd
                    dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
                close(fd[0]);
                check_cmd(node->cmd, lst_env);
            }
            exit(g_exit);
        }
        else
            wait(NULL);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        cmd_num--;
        while (check_redir(node))
            node = node->next;
        node = node->next;
        if (node && node->type == PIPE)
            node = node->next;
    }
    dup2(s_in, STDIN_FILENO); //fd_reset();
    close(s_in);
    return (0);
}
