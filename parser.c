/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:04:53 by mjlem             #+#    #+#             */
/*   Updated: 2022/07/19 22:18:47 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("%s--%c\n", tmp->arg, tmp->type);
		tmp = tmp->next;
	}
}

void	print_list2(t_node *tokens)
{
	t_node	*tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("%s--%c\n", tmp->cmd, tmp->type);
		tmp = tmp->next;
	}
}

void	word(t_token **tokens, t_node **line)
{
	char	*tmp;

	tmp = NULL;
	while ((*tokens) && ((*tokens)->type == WORD || (*tokens)->type == W_SPACE))
	{
		tmp = ft_strjoin(tmp, (*tokens)->arg);
		(*tokens) = (*tokens)->next;
	}
	add_node(line, new_node(WORD, tmp));
}

void	parse_pipe(t_token **tokens, t_node **line)
{
	add_node(line, new_node(PIPE, NULL));
	(*tokens) = (*tokens)->next;
}

void	parse_re(t_node **line, t_token **tokens)
{
	int		type;
	char	*tmp;

	tmp = NULL;
	type = (*tokens)->type;
	(*tokens) = (*tokens)->next;
	if ((*tokens)->type == W_SPACE)
		(*tokens) = (*tokens)->next;
	while ((*tokens) && (*tokens)->type == WORD)
	{
		tmp = ft_strjoin(tmp, (*tokens)->arg);
		(*tokens) = (*tokens)->next;
	}
	add_node(line, new_node(type, tmp));
}

t_node	*parse(t_token **tokens)
{
	t_node	*line;

	line = NULL;
	while ((*tokens))
	{
		if ((*tokens)->type == WORD)
			word(tokens, &line);
		else if ((*tokens)->type == PIPE)
			parse_pipe(tokens, &line);
		else if ((*tokens)->type == OUT_REDIR || (*tokens)->type == RE_ADD
			|| (*tokens)->type == IN_REDIR || (*tokens)->type == HERE_DOC)
			parse_re(&line, tokens);
		else if ((*tokens)->type == W_SPACE)
			(*tokens) = (*tokens)->next;
	}
	return (line);
}

t_node	*parser(char *line)
{
	t_token	*tokens;
	t_node	*list;
	t_token	*tmp;

	list = NULL;
	tokens = lexer(line);
	if (!tokens)
	{
		printf("Error\n");
		return (list);
	}
	print_list(tokens);
	tmp = tokens;
	printf ("%d\n", pipeline(&tmp));
	list = parse(&tokens);
	print_list2(list);
	return (list);
}

// t_node *