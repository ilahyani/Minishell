/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:04:48 by mjlem             #+#    #+#             */
/*   Updated: 2022/08/01 00:15:50 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_pipe(t_token **tokens, int i)
{
	add_lst(tokens, lst_new("|", PIPE));
	return (i + 1);
}

int	my_redirection(t_token **tokens, char *line, int i)
{
	if (line[i] == '>' && line[i + 1] == '>')
	{
		add_lst(tokens, lst_new(">>", RE_ADD));
		return (i + 2);
	}
	else if (line[i] == '<' && line[i + 1] == '<')
	{
		add_lst(tokens, lst_new("<<", HERE_DOC));
		return (i + 2);
	}
	else if (line[i] == '>')
		add_lst(tokens, lst_new(">", OUT_REDIR));
	else
		add_lst(tokens, lst_new("<", IN_REDIR));
	return (i + 1);
}

int	single_quote(t_token **tokens, char *line, int i)
{
	int	s;

	s = i;
	while (line[i] && line[i] != '\'')
		i++;
	if (!line[i])
		return (-1);
	else
		add_lst(tokens, lst_new(ft_substr(line, s, i - s), SQ_STR));
	return (i + 1);
}

t_token	*lexer(char *line)
{
	int		i;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	while (line[i] && i > -1)
	{
		if (line[i] == '\'')
			i = single_quote(&tokens, line, i + 1);
		else if (line[i] == '\"')
			i = double_quote(&tokens, line, i + 1);
		else if (line[i] == '$')
			i = dollar_sign(&tokens, line, i);
		else if (line[i] == ' ' || line[i] == '\t')
			i = space(&tokens, line, i);
		else if (line[i] == '<' || line[i] == '>')
			i = my_redirection(&tokens, line, i);
		else if (line[i] == '|')
			i = my_pipe(&tokens, i);
		else if (special_char(line[i]))
			return (NULL);
		else
			i = get_word(&tokens, line, i);
	}
	if (i == -1)
		return (NULL);
	return (tokens);
}
