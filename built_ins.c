#include "minishell.h"

int my_echo(int ac, char *av)
{
    int i;
    int new_line;

    if (ac == 1)
    {
        printf("\n");
        return (0);
    }
    i = 1;
    if (!ft_strncmp(av, "-n", sizeof(av)))
    {
        new_line = 0;
        i++;
    }
    while (i < ac)
    {
        printf("%s", av);
        if (i++ != ac - 1)
            printf(" ");
    }
    if (new_line)
        printf("\n");
    return (0);
}

int my_pwd(int ac, char *av)
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


int my_cd(int ac, char *av)
{

    if (ac > 2)
        printf("string not in pwd\n");
    else if (ac == 1)
    {
        chdir(getenv("HOME"));
        // if (chdir(getenv("HOME")) == 0)
        //     printf("%s\n", getcwd(cwd, 1000));
        // else
        //     printf("No such file or directory\n");
    }
    else
    {
        chdir(av);
        // if (chdir(av[1]) == 0)
        //     printf("%s\n", getcwd(cwd, 1000));
        // else
        //     printf("No such file or directory\n");
    }
    return (0);
}
