#include "sss.h"

int copy_idandexe(char *command)
{
    pid_t pid;

    pid = fork();

    if (pid == 0)
    {
    execl(command, command, NULL);
    perror("RIP, can't even execute properly");
    exit(1);
    }
    else
    {
        wait(NULL);
    }
    return (1);
}

int main(void)
{
    size_t length;
    char *line = NULL;
    int null_checker;

    while (1)
    {
        printf("$ ");
        fflush(stdout);

        if(getline(&line, &length, stdin) == -1)
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
        copy_idandexe(line);
    }
    free(line);
    printf("\n");
    return (0);
}