/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 00:05:24 by mjlem             #+#    #+#             */
/*   Updated: 2022/08/12 21:07:07 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_pipe(t_token **tokens, t_node **line)
{
	add_node_parse(line, new_node(PIPE, add_to_table(NULL, NULL)));
	(*tokens) = (*tokens)->next;
}

char	*expand_exit_code(char *arg)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_itoa(g_status);
	tmp = ft_strjoin(tmp, arg + 2);
	free(arg);
	return (tmp);
}

void	var_expand(t_token **mv, t_env	**tmp)
{
	while ((*tmp))
	{
		if (!ft_strcmp((*mv)->arg + 1, (*tmp)->var))
		{
			free((*mv)->arg);
			(*mv)->arg = ft_strdup((*tmp)->value);
			break ;
		}
		(*tmp) = (*tmp)->next;
	}
	if (!(*tmp))
	{
		free((*mv)->arg);
		(*mv)->arg = ft_strdup("");
	}
}

t_token	*expand_var(t_token *tokens, t_env *list_env)
{
	t_env	*tmp;
	t_token	*mv;

	tmp = list_env;
	mv = tokens;
	while (mv)
	{
		if (heredoc_here(mv->type) && mv->type == EXPAND)
		{
			if (mv->arg[1] == '?')
				mv->arg = expand_exit_code(mv->arg);
			else
				var_expand(&mv, &tmp);
			tmp = list_env;
		}
		mv = mv->next;
	}
	return (tokens);
}

t_node	*move_1(t_node *node, t_node **origen, t_node *head)
{
	t_node	*tmp3;
	t_node	*tmp2;

	tmp3 = (*origen);
	tmp2 = head;
	if (head->type != WORD)
	{
		while (tmp3->next != head)
			tmp3 = tmp3->next;
		tmp3->next = node;
		while (tmp2->next != node)
			tmp2 = tmp2->next;
		tmp2->next = node->next;
		node->next = head;
		return (node);
	}
	return (NULL);
}
