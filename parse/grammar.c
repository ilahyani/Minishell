/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:14:48 by mjlem             #+#    #+#             */
/*   Updated: 2022/08/01 00:03:10 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirction(t_token **tokens)
{
	if ((*tokens)->type == W_SPACE)
		(*tokens) = (*tokens)->next;
	if ((*tokens)->type == OUT_REDIR || (*tokens)->type == IN_REDIR
		|| (*tokens)->type == HERE_DOC || (*tokens)->type == RE_ADD)
	{
		(*tokens) = (*tokens)->next;
		if (!(*tokens))
			return (-1);
		if ((*tokens)->type == W_SPACE)
			(*tokens) = (*tokens)->next;
		if ((*tokens) && ((*tokens)->type == WORD
				|| (*tokens)->type == EXPAND || (*tokens)->type == SQ_STR))
		{
			while ((*tokens) && ((*tokens)->type == WORD
					|| (*tokens)->type == EXPAND || (*tokens)->type == SQ_STR))
				(*tokens) = (*tokens)->next;
			return (1);
		}
		else
			return (-1);
	}
	return (0);
}

int	simple_cmd_elm(t_token **tokens)
{
	int	node;

	if (!(*tokens))
		return (0);
	if ((*tokens)->type == W_SPACE)
			(*tokens) = (*tokens)->next;
	if (!(*tokens))
		return (0);
	if ((*tokens)->type == WORD || (*tokens)->type == EXPAND
		|| (*tokens)->type == SQ_STR)
	{
		while ((*tokens) && ((*tokens)->type == WORD
				|| (*tokens)->type == EXPAND || (*tokens)->type == SQ_STR))
			(*tokens) = (*tokens)->next;
		return (1);
	}
	node = redirction(tokens);
	if (node > 0)
		return (1);
	else if (node == -1)
		return (-1);
	return (0);
}

int	check_pipe(t_token **tokens)
{
	int	node;

	if ((*tokens)->type == W_SPACE)
		(*tokens) = (*tokens)->next;
	if (!(*tokens))
		return (-1);
	if ((*tokens)->type == PIPE)
	{
		(*tokens) = (*tokens)->next;
		node = pipeline(tokens);
		return (node);
	}
	return (0);
}

int	simple_cmd(t_token **tokens)
{
	int	node;

	node = simple_cmd_elm(tokens);
	if (node > 0)
	{
		while (node > 0)
			node = simple_cmd_elm(tokens);
		if (node == -1)
			return (-1);
		else
			return (1);
	}
	return (0);
}

int	command(t_token **tokens)
{
	int	node;

	node = simple_cmd(tokens);
	if (node == -1 || node == 0)
		return (-1);
	return (1);
}

/*end of line || error*/	

/*skip space token */