#include "sss.h"

/**
 * test_split_string - Test the split_string function
 */
void test_split_string(void)
{
	char **words;
	int i = 0;

	printf("=== Testing split_string ===\n");
	words = split_string("ls -la /home", " ");

	if (words == NULL)
	{
		printf("Error: split_string returned NULL\n");
		return;
	}

	printf("Tokens:\n");
	while (words[i] != NULL)
	{
		printf("  [%d] %s\n", i, words[i]);
		free(words[i]);
		i++;
	}
	free(words);
	printf("\n");
}

/**
 * test_arg_print - Test the arg_print function
 */
void test_arg_print(void)
{
	char *test_args[] = {"program", "arg1", "arg2", "arg3", NULL};

	printf("=== Testing arg_print ===\n");
	arg_print(4, test_args);
	printf("\n");
}

/**
 * test_shell_loop - Test the shell_loop function
 */
void test_shell_loop(void)
{
	printf("=== Testing shell_loop ===\n");
	printf("Type commands and press Enter (Ctrl+D to exit)\n");
	shell_loop();
}

/**
 * main - Entry point, tests all functions
 */
int main(void)
{
	test_split_string();
	test_arg_print();
	test_shell_loop();
	return (0);
}