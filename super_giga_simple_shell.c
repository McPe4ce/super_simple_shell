#include "sss.h"

int copy_idandexe(char *command)
{
    pid_t pid;
    char *argv[] = {command, NULL};

    pid = fork();

    if (pid == -1)
    {
        return (-1);
    }

    if (pid == 0)
    {    
    execve(command, argv, environ);
    perror("RIP, can't even execute properly");
    exit(1);
    }
    else
    {
        if (wait(NULL) == -1)
        {
            perror("wait");
            return (-1);
        }
    }
    return (1);
}

int main(void)
{
    size_t length = 0;
    char *line = NULL;
    int null_checker;

    while (1)
    {
        if (isatty(STDIN_FILENO))
        {
            printf("$ ");
            fflush(stdout);
        }

        if (getline(&line, &length, stdin) == -1)
        {
            break;
        }
        for (null_checker = 0; line[null_checker] != '\0'; null_checker++)
        {
            if (line[null_checker] == '\n')
            {
                line[null_checker] = '\0';
                break;
            }
        }
        if (line[0] == '\0')
            {
                continue;
            }
        copy_idandexe(line);
    }
    free(line);
    printf("\n");
    return (0);
}