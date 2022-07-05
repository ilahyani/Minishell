/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:28:22 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/01 16:45:16 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	sizeof_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i]);
	return (i);
}

int	is_int(char *c)
{
	int	i;

	i = -1;
	if (c[0] == '-' || c[0] == '+')
		i++;
	while (c[++i])
		if (c[i] < '0' || c[i] > '9')
			return (0);
	return (1);
}

char	**parser(char *line)
{
	char **data;

	if (!line)
		return (0);
	data = ft_split(line, ' ');
	return (data);
}

char	**sort_tab(char **tab)
{
	char	**sorted;
	char	*tmp;
	int		i;
	int		j;

	sorted = (char **) malloc(sizeof(char *) * (sizeof_array(tab) + 1));
	i = -1;
	while (tab[++i])
		sorted[i] = ft_strdup(tab[i]);
	sorted[i] = NULL;
	i = 0;
    while (sorted[i])
    {
		j = i + 1;
        while (sorted[j])
        {
            if (ft_strcmp(sorted[i], sorted[j]) > 0)
            {
				tmp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = tmp;
            }
            j++;
        }
        i++;
    }
	return (sorted);
}

char	*strchr_plus(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s) + 1)
	{
		if (s[i] == (char)c)
			return ((char *)(s + (i + 1)));
		i++;
	}
	return (0);
}

int	find_char(char *s, char c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (i < (int)ft_strlen(s) + 1)
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (0);
}

t_env	*env_lstlast(t_env *lst)
{
	t_env	*last;

	if (!lst)
		return (0);
	last = lst;
	while (last->next)
		last = last->next;
	return (last);
}

void	env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = env_lstlast(*lst);
	last->next = new;
}

t_env	*env_lstnew(char *var, char *value)
{
	t_env	*res;

	res = (t_env *) malloc (sizeof(t_env));
	if (!res)
		return (0);
	res->var = ft_strdup(var);
    if (value)
        res->value = ft_strdup(value);
    else
        res->value = NULL;
	res->next = NULL;
	return (res);
}

t_env    *env_init(char **env, t_env *lst_env)
{
    char **buff;
    int i;

    i = -1;
    while (env[++i])
    {
        buff = ft_split(env[i], '=');
        if (!buff[1])
            buff[1] = NULL;
	    env_lstadd_back(&lst_env, env_lstnew(buff[0], buff[1]));
        free(buff[0]);
        free(buff[1]);
        free(buff);
    }
    return (lst_env);
}
