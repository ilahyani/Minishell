/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:49:12 by mjlem             #+#    #+#             */
/*   Updated: 2022/08/06 22:28:47 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "./parse/parse.h"
# include "./exec/execution.h"
# include <signal.h>

t_node	*parser(char *line, t_env *lst_env);
t_token	*expand_var(t_token *tokens, t_env *list_env);
void	ft_readline(t_env **lst_env);
void	interpret_cmd(t_node *cmd, t_env **lst_env);
void	check_cmd(char **cmd, t_env **lst_env);

#endif