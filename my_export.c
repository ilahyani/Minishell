/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:19:30 by ilahyani          #+#    #+#             */
/*   Updated: 2022/06/29 21:38:59 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_print(t_env *env)
{
    t_env *tmp;

	tmp = env;
    while (tmp)
    {
        if (tmp->value)
            printf("declare -x %s=\"%s\"\n", tmp->var, tmp->value);
        else
            printf("declare -x %s\n", tmp->var);
        tmp = tmp->next;
    }
}

t_env	*lst_copy(t_env *env)
{
	t_env	*copy;
	t_env	*tmp;

	copy = NULL;
	tmp = env;
	while (tmp)
	{
        if (tmp->value)
		    env_lstadd_back(&copy, env_lstnew(tmp->var, tmp->value));
        else
            env_lstadd_back(&copy, env_lstnew(tmp->var, NULL));
		tmp = tmp->next;
	}
	return (copy);
}

void    swap_data(t_env *node1, t_env *node2)
{
    char    *var_tmp;
    char    *value_tmp;

    var_tmp = node1->var;
    value_tmp = node1->value;
    node1->var = node2->var;
    node1->value = node2->value;
    node2->var = var_tmp;
    node2->value = value_tmp;
}

void	ft_sort(t_env *env)
{
	t_env	*lst_tmp;
	t_env	*lst_tmp2;

	lst_tmp = env;
    while (lst_tmp->next)
    {
		lst_tmp2 = lst_tmp->next;
        while (lst_tmp2)
        {
            if (ft_strcmp(lst_tmp2->var, lst_tmp->var) < 0)
                swap_data(lst_tmp2, lst_tmp);
            lst_tmp2 = lst_tmp2->next;
        }
        lst_tmp = lst_tmp->next;
    }
}

int error_check(char *str)
{
    if ((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z') || str[0] == '_')
        return (0);
    return (1);
}

char    *ft_strldup(char *src, size_t len)
{
    int     i;
    char    *dst;

    if (!src)
        return (NULL);
    dst = (char *) malloc((len + 1)*sizeof(char));
    i = -1;
    while (++i < (int) len)
        dst[i] = src[i];
    dst[i] = '\0';
    return (dst);
}

t_env	*env_lstnew_plus(char *buff)
{
	t_env	*res;
    char    **tab;

    if (!buff)
        return (NULL);
	res = (t_env *) malloc (sizeof(t_env));
	if (!res)
		return (NULL);
    if (!find_char(buff, '='))
    {
        tab = ft_split(buff, '=');
        res->var = ft_strdup(tab[0]);
        if (tab[1])
            res->value = ft_strdup(tab[1]);
        else
            res->value = NULL;
        res->next = NULL;
        free(tab[0]);
        free(tab[1]);
        free(tab);
    }
    else
    {
        res->var = ft_strldup(buff, find_char(buff, '='));
        res->value = ft_strdup(&buff[find_char(buff, '=') + 1]);
    }
	return (res);
}

int my_export(char **data, t_env *env)
{
    t_env   *sorted;
    t_env   *lst_tmp;
    int     i;

    sorted = NULL;
    sorted = lst_copy(env); //check if this is reversed
    ft_sort(sorted);
    if (sizeof_array(data) == 1)
        env_print(sorted);
    else
    {
        i = 0;
        while (data[++i])
        {
            if (error_check(data[i]))
                return (printf("minishell: export: `%s': not a valid identifier\n", data[i]), 1);
            lst_tmp = env;
            while (lst_tmp && ft_strncmp(lst_tmp->var, data[i], ft_strlen(lst_tmp->var)))
                lst_tmp = lst_tmp->next;
            if (lst_tmp && lst_tmp->value && !find_char(data[i], '='))
            {
                continue ;
            if (lst_tmp)
            {
                if (data[i][find_char(data[i], '=') - 1] == '+')
                    lst_tmp->value = ft_strjoin(lst_tmp->value, data[i] + find_char(data[i], '=') + 1);//free old value
                else
                {
                    lst_tmp->value = ft_strdup(&data[i][find_char(data[i], '=') + 1]);
            }
            else
                env_lstadd_back(&env, env_lstnew_plus(data[i]));
        }
    }
    return (0);
}
