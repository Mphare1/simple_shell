#include "main.h"

/**
 * my_exit - simple impl of exit.
 * @ptrs: structure containing all malloced memory
 */
void my_exit(shell_t *pts)
{
    unsigned int x;
    char *exit_str;
    exit_str = pts->input_token[1];
    if(exit_str != NULL || pts == NULL)
    {
        errno = 0;
        for(x = 0; exit_str[x] != '\0'; x++)
            errno = errno * 10 + (exit_str[x] - '0');
    }
    free_shell_t(pts);
    if(errno > 255)
        errno %= 256;
    exit(errno);
}
/**
  * print_env - prints out the current environment
  * @ptrs: structure containing all malloced memory
  */
void print_env(shell_t *pts)
{
    unsigned int x, y;
    
    char enld = '\n';
    (void)pts;
    
    if(environ == NULL)
        return;
    for(x = 0; environ[x] != NULL; x++)
    {
        y = _strlen(environ[x]);
        if(y != 0)
        {
            write(STDOUT_FILENO, environ[x], y);
            write(STDOUT_FILENO, &enld, 1);
        }
    }
    errno = 0;
}
