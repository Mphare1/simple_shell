#include "shell.h"


/**
 * _strtok - function that tokenizes a string with a given delimiter
 * @str: string to tokenize
 * @delim: delimiter to use for tokenization
 *
 * Return: pointer to the next token, or NULL if there are no more tokens
 */
char *_strtok(char *str, const char *delim)

{

	static char *t_start;
    static char *last, *ltt;
    int outer_count, inner_count;
    int w_present = 0;  /* boolean flag indicating whether the current character is a delimiter */

	if (str == NULL)
	{
	if (t_start == NULL || ltt == NULL)

			return (NULL);
		str = ltt + 1;

	}
	else
	last = str + _strlen(str);

	for (outer_count = 0; str + outer_count < last; outer_count++)

	{
	for (inner_count = 0; delim != NULL && delim[inner_count] != '\0'; inner_count++)

		{
		if (str[outer_count] == delim[inner_count])

			{
			if (w_present == 1)

	{
			str[outer_count] = '\0';

		ltt = str + outer_count;

		return (t_start);

	}

	break;

			}
		}

		if (delim[inner_count] == '\0' && w_present == 0)

		{ 

		w_present = 1;

			t_start = str + outer_count;

		}

	}


	ltt = NULL;

	if (w_present == 1)


		return (t_start);


	return (NULL);

}