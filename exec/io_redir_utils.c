/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:32:14 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/11 17:29:56 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	multi_redic_check(t_node *cmd)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = cmd;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == OUT_REDIR || tmp->type == IN_REDIR
			|| tmp->type == RE_ADD || tmp->type == HERE_DOC)
			i++;
		tmp = tmp->next;
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
