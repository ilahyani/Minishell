/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:19:57 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/08 06:14:48 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_pwd(void)
{
	char	*cwd;

	cwd = NULL;
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
