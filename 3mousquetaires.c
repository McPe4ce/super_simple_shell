#include "sss.h"

/**
 * thefatherexe - Executes a command in 5 different child processes
 * As the process launches, the PID is given to the copied process (fork())
 * we check if pid == 0 to be sure we are in the child process
 * we execl the command asked for 
 * and make the parent parent each time the child process is on going
 * Return: 0 (Success)
 */
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