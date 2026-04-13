#ifndef SSS_H
#define SSS_H
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

pid_t getppid();
int arg_print(int ac, char **av);
void shell_loop(void);
void _mygetline(void);
char** split_string(const char *str, const char *delimiters);
#endif