#include "sss.h"

int main(int ac, char **av, char **env)
{
    extern char **environ;

    while (*environ)
    {
        printf("%s\n", *environ);
        environ++;
    }
    return (0);
}
