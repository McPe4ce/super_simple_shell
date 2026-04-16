#include "sss.h"

/**
 * list_directory - Builds a linked list for the PATH directories
 * Return: head (Returned the start of the list)
 */
list_t *list_directory(void)
{
	char *copy, *token;
	char *path = _getenv("PATH");
	list_t *new_node, *head = NULL, *tail = NULL;

	if (path == NULL)
	{
		return (NULL);
	}
	copy = strdup(path);
	token = strtok(copy, ":");

	while (token != NULL)
	{
		new_node = malloc(sizeof(list_t));
		
		if (new_node == NULL)
		{
			return (NULL);
		}
		new_node->directory = strdup(token);
		new_node->next = NULL;

		if (head == NULL)
		{
			head = new_node;
		}
		else
		{
			tail->next = new_node;
		}
		tail = new_node;
		token = strtok(NULL, ":");
	}
	free(copy);
	return (head);
}
