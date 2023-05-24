#include "shell.h"

/**
 * exit_function - Function pointer for the exit function.
 * @shell: Structure containing all malloced memory.
 */
typedef void (*exit_function)(shell_t *shell);

/**
 * exit_default - Default implementation of the exit function.
 * @shell: Structure containing all malloced memory.
 */
void exit_default(shell_t *shell)
{
	unsigned int i;
	char *exit_str = shell->input_token[1];
	if (exit_str != NULL || shell == NULL)
	{
		errno = 0;
		for (i = 0; exit_str[i] != '\0'; i++)
			errno = errno * 10 + (exit_str[i] - '0');
	}
	free_shell_t(shell);
	if (errno > 255)
		errno %= 256;
	exit(errno);
}

/**
 * print_env - Prints out the current environment.
 * @shell: Structure containing all malloced memory.
 */
void print_env(shell_t *shell)
{
	unsigned int i, k;
	char newline = '\n';
	(void)shell;
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
 * @shell: Structure containing all malloced memory.
 */
void my_exit(shell_t *shell)
{
	exit_function exit_fn = exit_default; // Default implementation
	if (shell->input_token[1] != NULL)
	{
		if (strcmp(shell->input_token[1], "printenv") == 0)
		{
			exit_fn = print_env; // Use print_env function for "exit printenv"
		}
	}
	exit_fn(shell); // Call the selected exit function
}
