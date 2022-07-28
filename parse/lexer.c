/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:04:48 by mjlem             #+#    #+#             */
/*   Updated: 2022/07/28 19:05:28 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_pipe(t_token **tokens, int i)
{
	add_lst(tokens, lst_new("|", PIPE));
	return (i + 1);
}

int	redirection(t_token **tokens, char *line, int i)
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

int	reserved_char(char c)
{
	if (c == '`' || c == '$' || c == '&' || c == '(' || c == ')' || c == ';'
		|| c == '!' || c == '\'' || c == '\"' || c == '>' || c == '<'
		|| c == ' ' || c == '\t'|| c == '|'|| c == '\\')
		return (0);
	return (1);
}

int	special_char(char c)
{
	if (c == '`' || c == '#' || c == '&' || c == '('
		|| c == ')' || c == ';' || c == '!' || c == '\\')
		return (1);
	return (0);
}
int	var_delimiter(char c)
{
	if (!(c >= '0' && c <= '9') && !(c >= 'A' && c <= 'Z')
		&& !(c >= 'a' && c <= 'z') && c != '_' && c != '?')
		return (0);
	return (1);
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

int	dollar_sign(t_token **tokens, char *line, int i)
{
	int	s;

	s = i;
	i++;
	if (line[i])
	{
		while (line[i] && var_delimiter(line[i]))
			i++;
		add_lst(tokens, lst_new(ft_substr(line, s, i - s), EXPAND));		
	}
	else
		add_lst(tokens, lst_new(ft_substr(line,s, i - s), WORD));
	return (i);
}

int	double_quote(t_token **tokens, char *line, int i)
{
	int	s;

	s = i;
	while (line[i] && line[i] != '\"')
	{
		if (line[i] == '$')
		{
			if (i > s)
			{
				add_lst(tokens, lst_new(ft_substr(line, s, i - s), WORD));
				s = i;
			}
			i++;
			if (line[i] && line[i] == '\"')
				break;
			while (line[i] && var_delimiter(line[i]))
				i++;
			if (!line[i])
				return (-1);
			else
			{
				add_lst(tokens, lst_new(ft_substr(line, s, i - s), EXPAND));
				if (line[i] == '\"')
					return (i + 1);
				s = i;
			}
		}
		if (line[i] != '$')
			i++;
	}
	if (!line[i])
		return (-1);
	else
		add_lst(tokens, lst_new(ft_substr(line, s, i - s), WORD));
	return (i + 1);
}

int	get_word(t_token **tokens, char *line, int i)
{
	int	s;

	s = i;
	while (line[i] && reserved_char(line[i]))
		i++;
	add_lst(tokens, lst_new(ft_substr(line, s, i - s), WORD));
	return (i);
}

int	space(t_token **tokens, char *line, int i)
{
	int	s;

	s = i;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (s == 0)
		return (i);
	add_lst(tokens, lst_new(" ", W_SPACE));
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
		if (line[i] == '\'')
			i = single_quote(&tokens, line, i + 1);
		else if (line[i] == '\"')
			i = double_quote(&tokens, line, i + 1);
		else if (line[i] == '$')
			i = dollar_sign(&tokens, line, i);
		else if (line[i] == ' ' || line[i] == '\t')
			i = space(&tokens, line, i);
		else if (line[i] == '<' || line[i] == '>')
			i = redirection(&tokens, line, i);
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

/* echo $
echo $""
echo "$"
echo "$"""
echo ""$""
echo ""$ */