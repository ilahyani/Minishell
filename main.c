/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:28:26 by ilahyani          #+#    #+#             */
/*   Updated: 2022/06/18 12:22:02 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
    char    *line;
    char    **data; //MAKE DATA A STRUCT TO MAKA INTEGRATION WITH THE PARSER EASIER!
    t_list  *lst_env;
    int i;

    (void)ac;
    (void)av;
    lst_env = NULL;
    i = -1;
    while (env[++i])
	    ft_lstadd_back(&lst_env, ft_lstnew(env[i]));
    while (1)
    {
        line = readline("🐌🐌🐌 ~ ");
        if (!ft_strcmp(line, ""))
            return (0);
        // data = parser(line);
        data = ft_split(line, ' ');
        if (!data)
            return (0);
        if (!ft_strcmp(data[0], "pwd"))
            my_pwd(data);
        else if (!ft_strcmp(data[0], "cd"))
            my_cd(data);
        else if (!ft_strcmp(data[0], "echo"))
            my_echo(data);
        else if(!ft_strcmp(data[0], "exit"))
            my_exit(data);
        else if(!ft_strcmp(data[0], "export"))
            my_export(data, env);
        else if(!ft_strcmp(data[0], "env"))
            my_env(lst_env);
        else if(!ft_strcmp(data[0], "unset"))
            my_unset(lst_env, data);
        // if clear -> sig cmd+k default behavior
    }
    return (0);
}
