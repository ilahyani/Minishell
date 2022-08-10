/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:04:48 by mjlem             #+#    #+#             */
/*   Updated: 2022/08/10 16:48:47 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_pipe(t_token **tokens, int i)
{
	add_lst(tokens, lst_new(ft_strdup("|"), PIPE));
	return (i + 1);
}

int	my_redirection(t_token **tokens, char *line, int i)
{
	if (line[i] == '>' && line[i + 1] == '>')
	{
		add_lst(tokens, lst_new(ft_strdup(">>"), RE_ADD));
		return (i + 2);
	}
	else if (line[i] == '<' && line[i + 1] == '<')
	{
		add_lst(tokens, lst_new(ft_strdup("<<"), HERE_DOC));
		return (i + 2);
	}
	else if (line[i] == '>')
		add_lst(tokens, lst_new(ft_strdup(">"), OUT_REDIR));
	else
		add_lst(tokens, lst_new(ft_strdup("<"), IN_REDIR));
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

int	quotes(t_token **tokens, char *line, int i)
{
	if (line[i] == '\'')
		i = single_quote(tokens, line, i + 1);
	else if (line[i] == '\"')
		i = double_quote(tokens, line, i + 1);
	return (i);
}

t_token	*lexer(char *line)
{
	int		i;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	while (line[i] && i > -1)
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = quotes(&tokens, line, i);
		else if (line[i] == '$')
			i = dollar_sign(&tokens, line, i);
		else if (line[i] == ' ' || line[i] == '\t')
			i = space(&tokens, line, i);
		else if (line[i] == '<' || line[i] == '>')
			i = my_redirection(&tokens, line, i);
		else if (line[i] == '|')
			i = my_pipe(&tokens, i);
		else if (special_char(line[i]))
			return (free_token_lst(tokens), NULL);
		else
			i = get_word(&tokens, line, i);
	}
	if (i == -1)
		return (free_token_lst(tokens), NULL);
	return (tokens);
}
