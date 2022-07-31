/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:57:13 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/25 19:55:05 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    handler(int signum)
{
    if (signum == SIGINT)
    {
        // rl_on_new_line();
		// rl_redisplay();
        // write(1, "  \n", 3);
        write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
        g_glob.status = 1;
    }
}