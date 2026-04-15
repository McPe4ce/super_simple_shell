#include "sss.h"

int main(int ac, char **av, char **env)
{
    extern char **environ;

    printf("Environ lives here: %p\n", (void *)environ);
    printf("Env lives here: %p\n", (void *)env);

    return (0);
}