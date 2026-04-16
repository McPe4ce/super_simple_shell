#ifndef SSS_H
#define SSS_H
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

typedef struct list_s
{
	char *directory;
	struct list_s *next;
} list_t;

int arg_print(int ac, char **av);
void shell_loop(void);
void _mygetline(void);
char** split_string(const char *str, const char *delimiters);
int thefatherexe(void);
int pathfinder(const char *filename);
int copy_idandexe(char *command);
char *_getenv(const char *name);
int pathdir(void);

#endif