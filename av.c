#include "sss.h"

/**
 * main - Reads and prints the arguments 
 */
int arg_print(int argc, char **argv)
{
    while (*argv)
    {
        (void)argc;
        printf("%s\n", *argv);
        argv++;
    }
    return (0);
}
