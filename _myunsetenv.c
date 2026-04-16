#include "sss.h"

/**
 * _unsetenv - deletes a variable from the environment
 * @name: the variable name to delete
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name)
{
	int DAname = strlen(name);
	int index = 0;

	if (name == NULL)
	{
		return (NULL);
	}

	while (*environ)
	{
		if (strncmp(*environ, name, DAname) == 0 && (*environ)[DAname] == '=')
		{
			while (environ[index])
			{
				environ[index] = environ[index + 1];
				index++;
			}
		}
		index++;
	}
	return (0);
}
