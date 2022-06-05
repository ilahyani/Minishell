#include "minishell.h"

int main()
{
    char *line;

    while (1)
    {
        line = readline("[minishell][:)]~> ");
        if (!ft_strncmp(line, "test", sizeof(line)))
            printf("it's working\n");
        else if(!ft_strncmp(line, "exit", sizeof(line)))
            exit(0);
    }
}
