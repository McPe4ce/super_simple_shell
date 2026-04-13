#include "sss.h"

int thefatherexe(void)
{
    int counter;

    for (counter = 0; counter < 5; counter++)
    {
        pid_t pid;

        pid = fork();

        if (pid == 0)
        {
            execl("/bin/ls", "ls", "-l", "/tmp", (char*) NULL);
        }
        else
        {
            wait(NULL);
        }
    }
    return (0);
}