/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:28:26 by ilahyani          #+#    #+#             */
/*   Updated: 2022/07/01 17:17:01 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// int ft_expand(char **data)
// {
//     int i;
//     t_env   *expand;

//     expand = NULL;
//     i = -1;
//     while (data[++i])
//     {
//         if (sizeof_array(data) == 1)
//             env_lstadd_back(&expand, env_lstnew_plus(data[i]));
//     }
// }

int main(int ac, char **av, char **env)
{
    char    *line;
    char    **data;
    t_env  *lst_env;

    (void)ac;
    (void)av;
    lst_env = NULL;
    lst_env = env_init(env, lst_env);
    while (1)
    {
        line = readline("🐌🐌🐌 ~ ");
        if (!ft_strcmp(line, ""))
            return (0);
        data = ft_split(line, ' ');
        if (!data)
            return (0);
        if (!ft_strcmp(data[0], "pwd"))
            my_pwd();
        else if (!ft_strcmp(data[0], "cd"))
            my_cd(lst_env, data);
        else if (!ft_strcmp(data[0], "echo"))
            my_echo(data);
        else if(!ft_strcmp(data[0], "exit"))
            my_exit(data);
        else if(!ft_strcmp(data[0], "export"))
            my_export(data, lst_env);
        else if(!ft_strcmp(data[0], "env"))
            my_env(lst_env);
        else if(!ft_strcmp(data[0], "unset"))
            my_unset(lst_env, data);
        else
            ft_exec2(data, env);
        //expantion
        //free data
        //if clear -> sig cmd+k default behavior
    }
    return (0);
}
