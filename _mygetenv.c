#include "sss.h"

/**
 * *_getenv - Function that gets an environnement variable
 * @name: Name of the variable to get
 * Return: NULL (value)
 */
char *_getenv(const char *name)
{
    int index = 0;
    int DAname = strlen(name);
    extern char **environ;

    while (*environ)
    {
        if (strncmp(environ[index], name, DAname) == 0 
            && environ[index][DAname] == '=')
        {
            return (environ[index] + DAname + 1);
        }
        index++;
    }
    return (NULL);
}