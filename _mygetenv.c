#include "sss.h"

/**
 * *_getenv - Function that gets an environnement variable
 * @name: Name of the variable to get
 * Return: NULL (value)
 */
char *_getenv(const char *name)
{
	int DAname = strlen(name);
	char **env = environ;

	if (name == NULL || *name == '\0')
	{
		return (NULL);
	}
	
	while (*env)
	{
		if (strncmp(*env, name, DAname) == 0 && (*env)[DAname] == '=')
		{
			return (*env + DAname + 1);
		}
	}
	return (NULL);
}
