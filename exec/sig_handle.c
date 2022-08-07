/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:57:13 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/07 11:00:08 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_sig(char *context)
{
	if (!ft_strcmp(context, "main"))
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (!ft_strcmp(context, "heredoc"))
	{
		signal(SIGINT, heredoc_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (!ft_strcmp(context, "./minishell"))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, child_handler);
		signal(SIGQUIT, child_handler);
	}
}

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_glob.status = 1;
	}
}

void	child_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_glob.status = 130;
		printf("\n");
	}
	else if (signum == SIGQUIT)
	{
		g_glob.status = 131;
		printf("Quit: 3\n");
	}
}

void	heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "hh\n", 3);
		rl_replace_line("\0", 0);
		rl_done = 1;
		g_glob.status = 1;
		g_glob.here_doc = 0;
	}
}
