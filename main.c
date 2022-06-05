#include "minishell.h"

int main()
{
    char *line;

    while (1)
    {
        line = readline("[minishell][:)]~> ");
        if (!ft_strcmp(line, "test"))
            printf("it's working\n");
        else if(!ft_strcmp(line, "exit"))
            exit(0);
    }
}
