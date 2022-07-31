/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 00:05:24 by mjlem             #+#    #+#             */
/*   Updated: 2022/08/01 00:05:37 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_exit_code(char *arg)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp2;
	int		l;

	i = 0;
	j = 1;
	l = 0;
	tmp = malloc(ft_strlen(arg));
	while (arg[j])
	{
		if (j == 1)
		{
			tmp2 = ft_itoa(g_glob.status);
			while (tmp2[i])
			{
				tmp[i] = tmp2[l];
				i++;
				l++;
			}
			j++;
		}
		tmp[i] = arg[j];
		j++;
		i++;
	}
	tmp[i] = '\0';
	free(arg);
	return (tmp);
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
			{	
				while (tmp)
				{
					if (!ft_strcmp(mv->arg + 1, tmp->var))
					{
						free(mv->arg);
						mv->arg = ft_strdup(tmp->value);
						break ;
					}
					tmp = tmp->next;
				}
				if (!tmp)
				{
					free(mv->arg);
					mv->arg = ft_strdup("");
				}
			}
			tmp = list_env;
		}
		mv = mv->next;
	}
	return (tokens);
}
