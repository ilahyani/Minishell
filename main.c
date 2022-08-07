/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:28:26 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/07 17:21:46 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_env	*lst_env;

	(void) ac;
	(void) av;
	lst_env = NULL;
	env_init(env, &lst_env);
	rl_catch_signals = 0;
	ft_readline(&lst_env);
	return (g_status);
}

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
		if (!ft_strcmp(line, ""))
			continue ;
		cmd = parser(line, *lst_env);
		if (cmd)
			interpret_cmd(cmd, lst_env);
		else
			printf("syntax error\n");
		if (ft_strlen(line) > 0)
			add_history(line);
	}
	free(line);
	printf("\bight I'mma head out\n");
	exit(g_status);
}

void	interpret_cmd(t_node *cmd, t_env **lst_env)
{
	int		s_fd[2];
	int		status;

	s_fd[1] = dup(1);
	s_fd[0] = dup(0);
	status = 0;
	if (find_char_2(cmd, PIPE))
		g_status = ft_pipe(cmd, *lst_env);
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
}

void	check_cmd(char **cmd, t_env **lst_env)
{
	if (!ft_strcmp(cmd[0], "pwd"))
		g_status = my_pwd();
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
