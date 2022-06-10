/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:28:26 by ilahyani          #+#    #+#             */
/*   Updated: 2022/06/07 14:57:51 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
    char    *line;
    //char    *av[2]={"ls", NULL};
    char    **data;
    // int     i;
    pid_t   parent;

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
            exit(0);
        else
            ft_exec(data);
    }
    return (0);
}
