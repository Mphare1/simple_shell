#include "main.h"

/**
 * _strtok - tokenizes a string
 * @str: string to tokenize
 * @delimiter: string that contains the delimiters
 * Return: pointer to position in string of a null-terminated word.
 */
char *_strtok(char *str, const char *delimiter)
{
    static char *w_start, *end_str, *end;
    int word_found = 0;

    if (str == NULL)
    {
        if (w_start == NULL || end == NULL)
            return NULL;
        str = end + 1;
    }
    else
        end_str = str + strlen(str);

    for (int x = 0; str + x < end_str; x++)
    {
        int y;
        for (y = 0; delimiter != NULL && delimiter[y] != '\0'; y++)
        {
            if (str[x] == delimiter[y])
            {
                if (word_found == 1)
                {
                    str[x] = '\0';
                    end = str + x;
                    return w_start;
                }
                break;
            }
        }
        if (delimiter[y] == '\0' && word_found == 0)
        {
            word_found = 1;
            w_start = str + x;
        }
    }

    end = NULL;
    if (word_found == 1)
        return w_start;

    return NULL;
}
