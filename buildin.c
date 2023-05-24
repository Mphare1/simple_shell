#include "shell.h"

/**
 * ................
 * ................
 */
void my_exit(shell_t *pts)
{
	unsigned int as;
	char *end_str = pts->input_token[1];
    
	if (end_str != NULL || pts == NULL)
	{
		errno = 0;
		for (as = 0; end_str[as] != '\0'; as++)
			errno = errno * 10 + (end_str[as] - '0');
	}
	free_shell_t(pts);
	if (errno > 255)
		errno %= 256;
	exit(errno);
}
/**
 * ................
 * ................
 */
void print_env(shell_t *pts)
{
	unsigned int as, x;
	char n_line = '\n';
	(void)pts;
	if (environ == NULL)
		return;

	for (as = 0; environ[as] != NULL; as++)
	{
		x = _strlen(environ[as]);
		if (x != 0)
		{
			write(STDOUT_FILENO, environ[as], x);

			write(STDOUT_FILENO, &n_line, 1);
		}
	}
	errno = 0;
}