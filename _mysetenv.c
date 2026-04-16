#include "sss.h"

/**
 * add_env - adds a new environment variable to environ
 * @name: the variable name
 * @value: the variable value
 * Return: 0 on success, -1 on failure
 */

static int add_env(const char *name, const char *value)
{
	int index = 0, dedex = 0;
	char **new_environ;

	while (environ[index])
	{
		index++;
	}

	new_environ = malloc(sizeof(char *) * (index + 2));

	if (new_environ == NULL)
	{
		return (-1);
	}

	while (dedex < index)
	{
		new_environ[dedex] = environ[dedex];
		dedex++;
	}
	new_environ[index] = malloc(strlen(name) + strlen(value) + 2);

	if (new_environ[index] == NULL)
	{
		return (-1);
	}
	sprintf(new_environ[index], "%s=%s", name, value);
	new_environ[index + 1] = NULL;
	environ = new_environ;

	return (0);
}

/**
 * _setenv - changes or adds an environment variable
 * @name: the variable name
 * @value: the variable value
 * @overwrite: if 0, do not overwrite an existing variable
 * Return: 0 on success, -1 on failure
 */

int _setenv(const char *name, const char *value, int overwrite)
{
	int DAname = strlen(name);
	char *new_name;

	if (name == NULL || value == NULL)
	{
		return (NULL);
	}

	while (*environ)
	{
		if (strncmp(*environ, name, DAname) == 0 && (*environ)[DAname] == '=')
		{
			if (overwrite == 0)
			{
				return (0);
			}
				new_name = malloc(DAname + strlen(value) + 2);

				if (new_name == NULL)
				{
					return (-1);
				}
				sprintf(new_name, "%s=%s", name, value);
				free(*environ);
				*environ = new_name;

				return (0);
		}
		environ++;
	}
	return (add_env(name, value));
}
