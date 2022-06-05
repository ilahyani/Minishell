#include "minishell.h"

int my_cd(int ac, char **av)
{
    char    *cwd;

    cwd = NULL;
    if (ac > 2)
        printf("string not in pwd\n");
    else if (ac == 1)
    {
        if (chdir(getenv("HOME")) == 0)
            printf("%s\n", getcwd(cwd, 1000));
        else
            printf("No such file or directory\n");
    }
    else
    {
        if (chdir(av[1]) == 0)
            printf("%s\n", getcwd(cwd, 1000));
        else
            printf("No such file or directory\n");
    }
    return (0);
}
