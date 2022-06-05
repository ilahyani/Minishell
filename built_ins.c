#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int my_echo(int ac, char **av)
{
    int i;
    int new_line;

    if (ac == 1)
    {
        printf("\n");
        return (0);
    }
    i = 1;
    if (!ft_strcmp(av[i], "-n"))
    {
        new_line = 0;
        i++;
    }
    while (i < ac)
    {
        printf("%s", av[i]);
        if (i++ != ac - 1)
            printf(" ");
    }
    if (new_line)
        printf("\n");
    return (0);
}

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
