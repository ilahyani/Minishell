/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redir_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:37:23 by ilahyani          #+#    #+#             */
/*   Updated: 2022/08/07 22:31:43 by mjlem            ###   ########.fr       */
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

int	dollar_sign_here_doc(t_env *lst_env, char *arg, int fd, int i)
{
	int		s;
	char	*var;
	t_env	*tmp;

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
	return (i);
}
