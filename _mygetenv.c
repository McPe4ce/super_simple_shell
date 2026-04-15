#include "sss.h"

/**
 * *_getenv - Function that gets an environnement variable
 * @name: Name of the variable to get
 * Return: NULL (value)
 */
char *_getenv(const char *name)
{
    int DAname = strlen(name);
    extern char **environ;

    while (*environ)
    {
        if (strncmp(*environ, name, DAname) == 0 && (*environ)[DAname] == '=')
        {
            return (*environ + DAname + 1);
        }
        environ++;
    }
    return (NULL);
}
