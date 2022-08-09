/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:28:26 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/09 22:40:48 by ilahyani         ###   ########.fr       */
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
	free_list(lst_env);
	return (g_status);
}
