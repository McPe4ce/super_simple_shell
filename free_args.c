#include "sss.h"

/**
 * free_args - Frees the arguments of the array one by one before freeing
 * the array
 * @args: Arguments
 */
void free_args(char **args)
{
	int indexor = 0;

	if (!args)
	{
		return;
	}
	while (args[indexor])
	{
		free(args[indexor]);
		indexor++;
	}
	free(args);
}
