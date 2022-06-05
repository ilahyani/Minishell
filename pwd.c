#include "minishell.h"

int my_pwd(int ac, char **av)
{
    char *cwd;

    (void) av;
    cwd = NULL;
    if (ac > 1)
        printf("Too many arguments\n");
    else
        printf("%s\n", getcwd(cwd, 1000));
    return (0);
}
