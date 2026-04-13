#include "sss.h"

/**
 * my_getline - Function that replicates getline()
 * fgets here reads the string and if it fails, return NULL
 * length takes the length of temp
 * deletes the new line read by fgets and replaces it by NULL char
 * allocates the exact memory for the string
 */
char *my_getline(FILE *fp) 
{
    int len;

    char temp[4096];
    
    if (fgets(temp, sizeof(temp), fp) == NULL) 
    {
        return NULL;
    }
    
    int len = strlen(temp);

    if (temp[len-1] == '\n')
    {
        temp[len-1] = '\0';
    }
    
    char *line = malloc(strlen(temp) + 1);
    strcpy(line, temp);
    
    return (line);
}
