/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:19:30 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/25 19:54:29 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void    fill_node(char *buff, t_env **lst)
{
    char **tab;

    tab = ft_split(buff, '=');
    (*lst)->var = ft_strdup(tab[0]);
    if (tab[1])
        (*lst)->value = ft_strdup(tab[1]);
    else
        (*lst)->value = NULL;
    (*lst)->next = NULL;
    free_tab(tab); 
}

t_env	*exprt_lstnew(char *buff)
{
	t_env	*res;

    if (!buff)
        return (NULL);
	res = (t_env *) malloc (sizeof(t_env));
	if (!res)
		return (NULL);
    if (!find_char(buff, '='))
        fill_node(buff, &res);
    else if (find_char(buff, '+'))
    {
        res->var = ft_strldup(buff, find_char(buff, '+'));
        res->value = ft_strdup(strchr_plus(buff, '=')); 
    }
    else
    {
        res->var = ft_strldup(buff, find_char(buff, '='));
        res->value = ft_strdup(strchr_plus(buff, '='));
    }
	return (res);
}

int check_error(char *buff)
{
    if (!ft_isalpha(buff[0]) && buff[0] != '_')
        return (1);
    if (find_char(buff, '+') && !find_char(buff, '='))
        return(1);
    return (0);
}

int check_var(char *buff, t_env *lst)
{
    if (find_char(buff, '='))
    {
        if ((find_char(buff, '+') && !ft_strcmp(lst->var, ft_strldup(buff, find_char(buff, '+')))))
            return (1);
        else if (find_char(buff, '=') && !ft_strcmp(lst->var, ft_strldup(buff, find_char(buff, '='))))
            return (1);
        else if (!ft_strcmp(lst->var, buff))
            return (1);
    }
    return (0);
}

void update_exp(char *buff, t_env **lst)
{
    if (buff[find_char(buff, '=') - 1] == '+') 
    {
        if ((*lst)->value)
            (*lst)->value = ft_strjoin((*lst)->value, strchr_plus(buff, '='));//free old value
        else
            (*lst)->value = ft_strdup(strchr_plus(buff, '='));   
    }
    else
        (*lst)->value = ft_strdup(strchr_plus(buff, '='));
}

int my_export(char **data, t_env *env)
{
    t_env   *sorted;
    t_env   *lst_tmp;
    int     i;

    if (!env)
        return (0);
    sorted = NULL;
    sorted = lst_copy(env);
    ft_sort(sorted);
    if (sizeof_array(data) == 1 || data[1][0] == '#' || data[1][0] == '$')
        env_print(sorted);
    else
    {
        i = 0;
        while (data[++i])
        {
            if (check_error(data[i]))
                return (err_print(data[i], "not a valid identifier"), 1); //stderr
            lst_tmp = env;
            while (lst_tmp)
            {
                if (check_var(data[i], lst_tmp))
                    break;
                lst_tmp = lst_tmp->next;
            }
            if (lst_tmp && !find_char(data[i], '='))
                continue ;
            else if (lst_tmp)
                update_exp(data[i], &lst_tmp);
            else
                env_lstadd_back(&env, exprt_lstnew(data[i]));
        }
    }
    // free(sorted);
    return (0);
}
