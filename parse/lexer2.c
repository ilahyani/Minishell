/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 23:59:01 by mjlem             #+#    #+#             */
/*   Updated: 2022/08/08 02:31:02 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dollar_sign(t_token **tokens, char *line, int i)
{
	int	s;

	s = i;
	i++;
	if (line[i] && line[i] != ' ' && var_delimiter(line, i))
	{
		while (line[i] && var_delimiter(line, i))
			i++;
		add_lst(tokens, lst_new(ft_substr(line, s, i - s), EXPAND));
	}
	else
		add_lst(tokens, lst_new(ft_substr(line, s, i - s), WORD));
	return (i);
}

int	handel_dollar_sign(t_token **tokens, char *line, int i, int s)
{
	add_lst(tokens, lst_new(ft_substr(line, s, i - s), WORD));
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
				s = handel_dollar_sign(tokens, line, i, s);
			i++;
			if (line[i] && line[i] == '\"')
				break ;
			while (line[i] && var_delimiter(line, i))
				i++;
			if (!line[i])
				return (-1);
			add_lst(tokens, lst_new(ft_substr(line, s, i - s), EXPAND));
			if (line[i] == '\"')
				return (i + 1);
			s = i;
		}
		if (line[i] != '$')
			i++;
	}
	return (double_qoute_return(tokens, line, i, s));
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
	add_lst(tokens, lst_new(ft_strdup(" "), W_SPACE));
	return (i);
}
