/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:04:53 by mjlem             #+#    #+#             */
/*   Updated: 2022/08/13 15:22:14 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	word(t_token **tokens, t_node **line)
{
	char	*tmp;
	char	**tmp_2d;

	tmp = NULL;
	tmp_2d = NULL;
	while ((*tokens) && ((*tokens)->type == WORD || (*tokens)->type == W_SPACE
			|| (*tokens)->type == EXPAND || (*tokens)->type == SQ_STR))
	{
		tmp = ft_strjoin(tmp, (*tokens)->arg);
		(*tokens) = (*tokens)->next;
		if (!(*tokens) || (*tokens)->type == W_SPACE)
		{
			if ((*tokens) && (*tokens)->type == W_SPACE)
				(*tokens) = (*tokens)->next;
			tmp_2d = add_to_table(tmp_2d, tmp);
			free(tmp);
			tmp = NULL;
		}
	}
	tmp_2d = add_to_table(tmp_2d, tmp);
	if (tmp)
		free(tmp);
	add_node_parse(line, new_node(WORD, tmp_2d));
}

void	parse_re(t_node **line, t_token **tokens)
{
	int		type;
	char	*tmp;
	char	**tmp2;

	tmp = NULL;
	tmp2 = NULL;
	type = (*tokens)->type;
	(*tokens) = (*tokens)->next;
	if ((*tokens)->type == W_SPACE)
		(*tokens) = (*tokens)->next;
	if ((*tokens) && ((*tokens)->type == WORD
			|| (*tokens)->type == EXPAND || (*tokens)->type == SQ_STR))
	{
		while ((*tokens) && ((*tokens)->type == WORD
				|| (*tokens)->type == EXPAND || (*tokens)->type == SQ_STR))
		{
			tmp = ft_strjoin(tmp, (*tokens)->arg);
			(*tokens) = (*tokens)->next;
		}
		tmp2 = add_to_table(tmp2, tmp);
		add_node_parse(line, new_node(type, tmp2));
	}
	if (tmp)
		free(tmp);
}

void	parse_heredoc(t_node **line, t_token **tokens)
{
	char	*tmp;
	char	**tmp2;
	int		type;

	tmp = NULL;
	tmp2 = NULL;
	type = (*tokens)->type;
	(*tokens) = (*tokens)->next;
	if ((*tokens)->type == W_SPACE)
		(*tokens) = (*tokens)->next;
	if ((*tokens) && ((*tokens)->type == WORD
			|| (*tokens)->type == EXPAND || (*tokens)->type == SQ_STR))
	{
		while ((*tokens) && ((*tokens)->type == WORD
				|| (*tokens)->type == EXPAND || (*tokens)->type == SQ_STR))
		{
			tmp = ft_strjoin(tmp, (*tokens)->arg);
			(*tokens) = (*tokens)->next;
		}
		tmp2 = add_to_table(tmp2, tmp);
		add_node_parse(line, new_node(type, tmp2));
	}
	if (tmp)
		free(tmp);
}

t_node	*parse(t_token **tokens)
{
	t_node	*line;

	line = NULL;
	while ((*tokens))
	{
		if ((*tokens)->type == WORD || (*tokens)->type == EXPAND
			|| (*tokens)->type == SQ_STR)
			word(tokens, &line);
		else if ((*tokens)->type == PIPE)
			parse_pipe(tokens, &line);
		else if ((*tokens)->type == OUT_REDIR || (*tokens)->type == RE_ADD
			|| (*tokens)->type == IN_REDIR)
			parse_re(&line, tokens);
		else if ((*tokens)->type == W_SPACE)
			(*tokens) = (*tokens)->next;
		else if ((*tokens)->type == HERE_DOC)
			parse_heredoc(&line, tokens);
	}
	return (line);
}

t_node	*parser(char *line, t_env *lst_env)
{
	t_token	*tokens;
	t_node	*list;
	t_token	*tmp;
	t_token	*tof;

	list = NULL;
	tof = NULL;
	tokens = lexer(line);
	if (!tokens)
		return (list);
	tmp = tokens;
	tof = tokens;
	if (pipeline(&tmp) == 1)
	{
		tokens = expand_var(tokens, lst_env);
		tof = tokens;
		list = parse(&tokens);
		list = adjuste_list(list);
	}
	free_token_lst(tof);
	return (list);
}
