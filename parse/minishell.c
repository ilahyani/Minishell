/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:04:51 by mjlem             #+#    #+#             */
/*   Updated: 2022/07/25 19:57:01 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	main(int ac, char **av, char **env)
// {
// 	char	*line;
// 	t_env	*lst_env;

// 	(void)av;
// 	env_init(env, &lst_env);
// 	if (ac == 1)
// 	{
// 		while (1)
// 		{
// 			line = readline("🐌");
// 			if (line && line[0])
// 				parser(line, lst_env);
// 			add_history(line);
// 		}
// 	}
// }
/*  export LDFLAGS="-L/Users/mjlem/.brew/opt/readline/lib"
	export CPPFLAGS="-I/Users/mjlem/.brew/opt/readline/include"*/