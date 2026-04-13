#include "sss.h"

/**
 * shell_loop - Function that prints $ and waits for the user to enter a cmd
 * HIW?: You initialise line to NULL first, while it runs, fflush forces the $
 * to be printed immediatly and getline() grabs the addresses of the intputs
 * Frees the allocated memory by getline()
 */
void shell_loop(void)
{
    char *line = NULL;
    size_t length;

    while (1)
    {
        printf("$ ");
        fflush(stdout);

        getline(&line, &length, stdin);

    }
    free(line);
}

int main(void)
{
    shell_loop();
    return (0);
}