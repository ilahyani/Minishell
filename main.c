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
    char    *av[2]={"ls", NULL};
    char    **data;
    // int     i;
    pid_t   child;

    while (1)
    {
        line = readline("🐌🐌🐌 ~ ");
        data = parser(line);
        if (!ft_strcmp(data[0], "pwd"))
            my_pwd(data);
        else if (!ft_strcmp(data[0], "cd"))
            my_cd(data);
        else if (!ft_strcmp(data[0], "echo"))
            my_echo(data);
        else if(!ft_strcmp(data[0], "exit"))
            exit(0);
        else
        {
            // i = -1;
            // while (data[++i])
                // ft_strlcpy(av[i], data[i], sizeof(data[i]));
            // printf("here\n");
            child = fork();
            if (child == 0)
                execve(data[0], av, NULL);
        }
    }
    return (0);
}
