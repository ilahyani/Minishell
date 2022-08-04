/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 23:51:21 by mjlem             #+#    #+#             */
/*   Updated: 2022/08/04 15:35:44 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipeline(t_token **tokens)
{
	int	node;

	node = command(tokens);
	if (node == -1)
		return (-1);
	if (!(*tokens))
		return (1);
	node = check_pipe(tokens);
	if (!node)
		return (1);
	return (node);
}

int	double_qoute_return(t_token **tokens, char *line, int i, int s)
{
	if (!line[i])
		return (-1);
	add_lst(tokens, lst_new(ft_substr(line, s, i - s), WORD));
	return (i + 1);
}
