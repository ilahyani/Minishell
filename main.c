/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:28:26 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/31 01:33:20 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: shell inception sig handling -> sigaction? let's go

void	check_cmd(char **cmd, t_env **lst_env)
{
	if (!ft_strcmp(cmd[0], "pwd"))
		g_glob.status = my_pwd();
	else if (!ft_strcmp(cmd[0], "cd"))
		g_glob.status = my_cd(*lst_env, cmd);
	else if (!ft_strcmp(cmd[0], "echo"))
		g_glob.status = my_echo(cmd);
	else if (!ft_strcmp(cmd[0], "export"))
		g_glob.status = my_export(cmd, *lst_env);
	else if (!ft_strcmp(cmd[0], "env"))
		g_glob.status = my_env(*lst_env, cmd);
	else if (!ft_strcmp(cmd[0], "unset"))
		g_glob.status = my_unset(lst_env, cmd);
	else if (!ft_strcmp(cmd[0], "exit"))
		my_exit(cmd);
	else
		g_glob.status = ft_exec(cmd, *lst_env);
}

void	ft_readline(t_env **lst_env)
{
	char	*line;
	t_node	*cmd;

	rl_catch_signals = 0;
	while (42)
	{
		line = readline("🐌🐌🐌 ~ ");
		if (!line)
			break ;
		if (!ft_strcmp(line, ""))
			continue ;
		cmd = parser(line, *lst_env);
		if (cmd)
		{
			if (find_char_2(cmd, PIPE))
				g_glob.status = ft_pipe(cmd, *lst_env);
			else if (find_char_2(cmd, OUT_REDIR) || find_char_2(cmd, IN_REDIR)
				|| find_char_2(cmd, RE_ADD) || find_char_2(cmd, HERE_DOC))
				g_glob.status = redir_io(cmd, *lst_env);
			else
				check_cmd(cmd->cmd, lst_env);
		}
		if (ft_strlen(line) > 0)
			add_history(line);
	}
	free(line);
	printf("\b   \b\bexit\n");
	exit(g_glob.status);
}

int	main(int ac, char **av, char **env)
{
	t_env	*lst_env;

	(void) ac;
	(void) av;
	lst_env = NULL;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	env_init(env, &lst_env);
	ft_readline(&lst_env);
	return (g_glob.status);
}
