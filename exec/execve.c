/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:19:07 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/10 14:11:46 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec(char **data, t_env *lst_env)
{
	char	*path;
	char	**env;

	env = NULL;
	path = NULL;
	env = list_to_tab(lst_env);
	if ((data[0][0] == '.' && data[0][1] == '/') || data[0][0] == '/')
		run_executable(data, env);
	else
	{
		path = get_path(data[0], lst_env);
		if (!path)
		{
			err_print(data[0], "No such file or directory");
			return (free_tab(env), 127);
		}
		else if (create_process(path, data, env))
		{
			err_print(data[0], "Command not found");
			free(path);
			exit(127);
		}
	}
	free(path);
	return (free_tab(env), g_status);
}
