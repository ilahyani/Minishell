/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redir_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:37:23 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/07 21:59:00 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_out_redir(t_redir *data, t_node *cmd, int append)
{
	struct stat	buf;

	if (!fstat((data)->out_red, &buf))
		if (close((data)->out_red) == -1)
			return (ft_putendl_fd("unexpected error", 2), 1);
	if (append)
		return (open(cmd->cmd[0], O_CREAT | O_RDWR | O_APPEND, S_IRWXU));
	return (open(cmd->cmd[0], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU));
}

int	set_in_redir(t_redir *data, t_node *cmd)
{
	struct stat	buf;

	if (!fstat((data)->in_red, &buf))
		if (close((data)->in_red) == -1)
			return (ft_putendl_fd("unexpected error", 2), 1);
	return (open(cmd->cmd[0], O_RDONLY, S_IRWXU));
}
