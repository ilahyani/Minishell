/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:32:14 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/07 22:31:37 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	multi_redic_check(t_node *cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd->type != PIPE)
	{
		if (cmd->type == OUT_REDIR || cmd->type == IN_REDIR
			|| cmd->type == RE_ADD || cmd->type == HERE_DOC)
			i++;
		cmd = cmd->next;
	}
	return (i);
}

char	*check_file(t_node *node)
{
	if (node->type == WORD)
		return (node->next->cmd[0]);
	else
		return (node->cmd[0]);
}

void	data_init(t_redir *data)
{
	data->cmd = NULL;
	data->in_red = -11;
	data->out_red = -11;
	data->her_doc = NULL;
}

void	fd_reset(int fd[2])
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void	print_fd(t_env *lst_env, char *arg, int fd)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			i++;
			i = dollar_sign_here_doc(lst_env, arg, fd, i);
		}
		else
		{
			ft_putchar_fd(arg[i], fd);
			i++;
		}
	}
	ft_putchar_fd('\n', fd);
}
