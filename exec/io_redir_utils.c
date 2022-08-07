/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:32:14 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/07 17:57:39 by mjlem            ###   ########.fr       */
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
	t_env	*tmp;
	int		i;
	int		s;
	char	*var;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			i++;
			s = i;
			while (arg[i] && arg[i] != ' ' && var_delimiter(arg, i))
				i++;
			var = ft_substr(arg, s, i - s);
			if (var[0] == '?')
				ft_putstr_fd(expand_exit_code(var), fd);
			else
			{		
				tmp = lst_env;
				while (tmp && ft_strcmp(tmp->var, var))
					tmp = tmp->next;
				if (tmp)
					ft_putstr_fd(tmp->value, fd);
			}
		}
		else
		{
			ft_putchar_fd(arg[i], fd);
			i++;
		}
	}
	ft_putchar_fd('\n', fd);
}
