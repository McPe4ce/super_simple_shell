#include "sss.h"
#define MAX_PATH_LEN 1024

/**
 * find_in_path - Gets the path of environement variable
 * and seeks if the file exists and is executable.
 * Here we check if the path isnt NULL, then split the directories
 * with our other function, we loop through dir sprintf prints it to the buffer
 * access checks if it is executable
 * Return: (0)
 */
int find_in_path(const char *filename)
{
    char **dirs;
    char *path_env;
    char fullpath[MAX_PATH_LEN];
    int found = 0; int index;

    path_env = getenv("PATH");
    
    if (!path_env)
    {
        fprintf(stderr, "which: PATH not set\n");
        return (1);
    }

    dirs = split_string(path_env, ":");
    
    if (!dirs)
    {
        return (1);
    }


    for (index = 0; dirs[index]; index++)
    {

        sprintf(fullpath, "%s/%s", dirs[index], filename);

        if (access(fullpath, X_OK) == 0)
        {
            printf("%s\n", fullpath);
            found = 1;
            break;
        }
    }

    for (int index = 0; dirs[index]; index++)
    {
        free(dirs[index]);
    }
    free(dirs);

    if (!found)
    {
        fprintf(stderr, "which: %s: not found\n", filename);
        return (1);
    }

    return (0);
}

int main(int argc, char *argv[])
{
    int status = 0;
    
    if (argc < 2)
    {
        fprintf(stderr, "Usage: which filename ...\n");
        return (1);
    }

    for (int index = 1; index < argc; index++)
    {
        // Track if any file wasn't found
        if (find_in_path(argv[index]) != 0)
        {
            status = 1;
        }
    }
    return status;
}