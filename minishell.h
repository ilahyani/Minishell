/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:49:12 by mjlem             #+#    #+#             */
/*   Updated: 2022/07/31 23:31:30 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "./parse/parse.h"
# include "./exec/execution.h"

t_node	*parser(char *line, t_env *lst_env);

void	ft_readline(t_env **lst_env);
void	interpret_cmd(t_node *cmd, t_env **lst_env);
void	check_cmd(char **cmd, t_env **lst_env);

#endif