/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:19:57 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/10 17:50:25 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_pwd(t_env *lst_env)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, sizeof(NULL));
	if (pwd)
		printf("%s\n", pwd);
	else
		printf("%s\n", ft_getenv("PWD", lst_env));
	free(pwd);
	return (0);
}
