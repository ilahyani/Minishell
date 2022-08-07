/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:57:13 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/07 22:13:08 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_signals(char *context)
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
		g_status = 1;
	}
}

void	child_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_status = 130;
		printf("\n");
	}
	else if (signum == SIGQUIT)
	{
		g_status = 131;
		printf("Quit: 3\n");
	}
}

void	heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_status = -1;
		rl_done = 1;
	}
	heredoc_here(RESET);
}
