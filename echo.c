#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2);

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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
