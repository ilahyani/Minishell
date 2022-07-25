/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:04:51 by mjlem             #+#    #+#             */
/*   Updated: 2022/07/25 16:43:54 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
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

void	env_init(char **env, t_env **lst_env)
{
    int		i;
    char	**buff;
	// char	cwd[PATH_MAX];

	if (!env) //set_env()
		return ;
    i = -1;
    while (env[++i])
    {
        buff = ft_split(env[i], '=');
        if (!buff[1])
            buff[1] = NULL;
	    env_lstadd_back(lst_env, env_lstnew(buff[0], buff[1]));
        free(buff[0]);
        free(buff[1]);
        free(buff);
    }
	//unset oldpwd & export oldpwd(empty) & export pwd=getcwd
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_env	*lst_env;

	(void)av;
	env_init(env, &lst_env);
	if (ac == 1)
	{
		while (1)
		{
			line = readline("🐌");
			if (line && line[0])
				parser(line, lst_env);
			add_history(line);
		}
	}
}
/*  export LDFLAGS="-L/Users/mjlem/.brew/opt/readline/lib"
	export CPPFLAGS="-I/Users/mjlem/.brew/opt/readline/include"*/