/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 23:55:53 by mjlem             #+#    #+#             */
/*   Updated: 2022/08/10 17:07:37 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	reserved_char(char c)
{
	if (c == '`' || c == '$' || c == '&' || c == '(' || c == ')' || c == ';'
		|| c == '!' || c == '\'' || c == '\"' || c == '>' || c == '<'
		|| c == ' ' || c == '\t' || c == '|' || c == '\\')
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

int	var_delimiter(char *line, int i)
{
	if (line[i] == '?' && line[i - 1] != '$')
		return (0);
	if ((line[i] >= '0' && line[i] <= '9') && line[i - 1] != '$')
		return (0);
	if (!(line[i] >= '0' && line[i] <= '9')
		&& !(line[i] >= 'A' && line[i] <= 'Z')
		&& !(line[i] >= 'a' && line[i] <= 'z')
		&& line[i] != '_' && line[i] != '?')
		return (0);
	return (1);
}

int	heredoc_here(int type)
{
	static int	flag = 0;

	if (type == HERE_DOC)
	{
		flag = 1;
		return (0);
	}
	if (type == EXPAND && flag)
	{
		flag = 0;
		return (0);
	}
	if (type == RESET)
		flag = 0;
	return (1);
}

char	**add_to_table(char **tmp2, char *tmp1)
{
	int		i;
	char	**tmp;

	i = 0;
	if (!tmp1)
	{
		tmp = NULL;
	}	
	if (!tmp2)
		tmp = malloc(sizeof(char *) * 2);
	else
	{
		while (tmp2[i])
			i++;
		tmp = malloc (sizeof(char *) * (i + 2));
		i = -1;
		while (tmp2[++i])
			tmp[i] = ft_strdup(tmp2[i]);
		free_tab(tmp2);
	}
	tmp[i++] = ft_strdup(tmp1);
	tmp[i] = NULL;
	return (tmp);
}
