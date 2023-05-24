#include "shell.h"

/**
 * exit_function - Function pointer for the exit function.
 * @ptrs: Structure containing all malloced memory.
 */
typedef void (*exit_function)(shell_t *ptrs);

/**
 * exit_default - Default implementation of the exit function.
 * @ptrs: Structure containing all malloced memory.
 */
void exit_default(shell_t *ptrs)
{
	unsigned int i;
	char *exit_str = ptrs->input_token[1];
	if (exit_str != NULL || ptrs == NULL)
	{
		errno = 0;
		for (i = 0; exit_str[i] != '\0'; i++)
			errno = errno * 10 + (exit_str[i] - '0');
	}
	free_shell_t(ptrs);
	if (errno > 255)
		errno %= 256;
	exit(errno);
}

/**
 * print_env - Prints out the current environment.
 * @ptrs: Structure containing all malloced memory.
 */
void print_env(shell_t *ptrs)
{
	unsigned int i, k;
	char newline = '\n';
	(void)ptrs;
	if (environ == NULL)
		return;
	for (i = 0; environ[i] != NULL; i++)
	{
		k = _strlen(environ[i]);
		if (k != 0)
		{
			write(STDOUT_FILENO, environ[i], k);
			write(STDOUT_FILENO, &newline, 1);
		}
	}
	errno = 0;
}

/**
 * my_exit - Implementation of the exit function using function pointers and mal_mem.
 * @ptrs: Structure containing all malloced memory.
 */
void my_exit(shell_t *ptrs)
{
	exit_function exit_fn = exit_default; // Default implementation
	if (ptrs->input_token[1] != NULL)
	{
		if (strcmp(ptrs->input_token[1], "printenv") == 0)
		{
			exit_fn = print_env; // Use print_env function for "exit printenv"
		}
	}
	exit_fn(ptrs); // Call the selected exit function
}
