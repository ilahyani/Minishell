/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 22:40:21 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/13 15:22:24 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_readline(t_env **lst_env)
{
	char	*line;
	t_node	*cmd;

	while (42)
	{
		set_signals("main");
		line = readline("🐌🐌🐌 ~ ");
		if (!line)
		{
			g_status = 0;
			break ;
		}
		if (empty_line(line))
			continue ;
		cmd = parser(line, *lst_env);
		if (cmd)
			interpret_cmd(cmd, lst_env);
		else
			cmd_error(cmd);
		if (ft_strlen(line) > 0)
			add_history(line);
		free(line);
	}
	free(line);
	printf("exit\n");
}

void	interpret_cmd(t_node *cmd, t_env **lst_env)
{
	int		s_fd[2];
	int		status;
	t_node	*lst;

	lst = cmd;
	s_fd[1] = dup(1);
	s_fd[0] = dup(0);
	status = 0;
	if (find_char_2(cmd, PIPE))
		g_status = exec_pipe(cmd, lst_env);
	else
	{
		if (find_char_2(cmd, OUT_REDIR) || find_char_2(cmd, IN_REDIR)
			|| find_char_2(cmd, RE_ADD) || find_char_2(cmd, HERE_DOC))
			status = redir_io(cmd, *lst_env);
		if (!status && cmd->type == WORD)
			check_cmd(cmd->cmd, lst_env);
		else if (status)
			g_status = 1;
	}
	fd_reset(s_fd);
	free_cmd(lst);
}

int	exec_pipe(t_node *cmd, t_env **lst_env)
{
	int	status;

	status = ft_pipe(cmd, *lst_env);
	if (status)
		return (1);
	return (0);
}

void	check_cmd(char **cmd, t_env **lst_env)
{
	if (!ft_strcmp(cmd[0], "pwd"))
		g_status = my_pwd(*lst_env);
	else if (!ft_strcmp(cmd[0], "cd"))
		g_status = my_cd(*lst_env, cmd);
	else if (!ft_strcmp(cmd[0], "echo"))
		g_status = my_echo(cmd);
	else if (!ft_strcmp(cmd[0], "export"))
		g_status = my_export(cmd, lst_env);
	else if (!ft_strcmp(cmd[0], "env"))
		g_status = my_env(*lst_env, cmd);
	else if (!ft_strcmp(cmd[0], "unset"))
		g_status = my_unset(lst_env, cmd);
	else if (!ft_strcmp(cmd[0], "exit"))
		my_exit(cmd);
	else
		g_status = ft_exec(cmd, *lst_env);
}

int	empty_line(char *line)
{
	char	*tmp;

	tmp = ft_strtrim(line, " ");
	if (!ft_strcmp(tmp, ""))
		return (free(line), free(tmp), 1);
	return (0);
}
