#include "sss.h"

/**
 * string_splitter - Splits a string and returns an array of each words
 */
char** split_string(const char *str, const char *delimiters)
{
    char *copy, *token, **result;
    int count = 0, index = 0;

    if (!str)
    {
        return NULL;
    }
    /*Creates a copy of the string strtok will modify*/
    copy = strdup(str);
    /* First pass: count the number of tokens to know array size */
    token = strtok(copy, delimiters);
    
    while (token)
    {
        count++;
        /* Get next token (NULL continues from previous position) */
        token = strtok(NULL, delimiters);
    }
    free(copy);
    
    result = malloc((count + 1) * sizeof(char*));
    
    copy = strdup(str);
    token = strtok(copy, delimiters);

    /* Second pass: fill the result array with duplicated tokens */
    while (token)
    {
        /* Store a copy of each token in the array */
        result[index++] = strdup(token);
        token = strtok(NULL, delimiters);
    }
    result[index] = NULL;
    free(copy);
    
    return (result);
}