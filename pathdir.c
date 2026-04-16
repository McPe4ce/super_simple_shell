#include "sss.h"

/**
 * pathdir - Prints each directories in the env var PATH
 */
int pathdir(void)
{
    char *copy;
    char *path = _getenv("PATH");
    char *token;
    
    if (path == NULL)
    {
        return (-1);
    }
    copy = strdup(path);
    token = strtok(copy, ":");
    
    while (token != NULL)
    {
        printf("%s\n", token);
        token = strtok(NULL, ":");
    }
    free(copy);
}