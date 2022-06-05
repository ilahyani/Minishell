#include "minishell.h"

int main()
{
    char    *line;

    while (1)
    {
        line = readline("bourggi 🐌~> ");
        if (!ft_strncmp(line, "pwd", sizeof(line)))
            my_pwd(1, NULL);
        else if (!ft_strncmp(line, "cd", sizeof(line)))
            my_cd(1, NULL);
        else if (!ft_strncmp(line, "echo", sizeof(line)))
            my_echo(2, "Hello World");
        else if(!ft_strncmp(line, "exit", sizeof(line)))
            exit(0);
    }
}
