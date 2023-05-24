#include "main.h"
#include <string.h>
#include <stdlib.h>

/**
 * _strlen - Calculate the length of a string
 * @str: The input string
 *
 * Return: The length of the string
 */
size_t _strlen(char *s_c)
{
	char *x = s_c;
	size_t c_char = 0;

	if (x == NULL)
		return c_char;

	while (*x++ != '\0')
		c_char++;

	return c_char;
}

/**
 * _strdup - Duplicate a string
 * @s: The string to duplicate
 *
 * Return: Pointer to the duplicated string, or NULL on failure
 */
char *_strdup(char *s)
{
	size_t x, length;
	char *cpy;

	x = length = 0;

	length = _strlen(s);

	cpy = malloc(sizeof(char) * (length + 1));
	if (!cpy)
		return NULL;

	for (x = 0; s[x]; x++)
		cpy[x] = s[x];

	cpy[x] = '\0';

	return cpy;
}

/**
 * _strcmp - Compare two strings
 * @str1: The first string
 * @str2: The second string
 *
 * Return: 0 if the strings are equal, non-zero otherwise
 */
int _strcmp(char *str1, char *str2)
{
	for (; *str1 != '\0' && *str2 != '\0'; str1++, str2++)
	{
		if (*str1 != *str2)
			return 1;
	}

	if (*str1 == '\0' && *str2 == '\0')
		return 0;

	return 1;
}




/**

 * tokenize_str - function that take a string split them up at a delimiters and

 * add them into a array.

 * @str: string to process.

 * @delim: delimiter to split at.

 *

 * Return: pointer to pointers

 */

char **tokenize_str(char *str, char *delim)

{

	size_t n_delim = 0;

	char *str_dup, *tok;

	char **tokens;



	if (!str || !delim)

		return (NULL);

	str_dup = _strdup(str);



	/* count the delimiters */

	tok = _strtok(str_dup, delim);

	while (tok)

	{

		n_delim++;

		tok = _strtok(NULL, delim);

	}

	/*free the str_dup*/

	free(str_dup);

	/* malloc for tokens based on n_delim + 1 for the Null */

	tokens = malloc(sizeof(char *) * (n_delim + 1));

	if (!tokens)

		return (NULL);



	/* tokenize str */

	tok = _strtok(str, delim);

	n_delim = 0;

	while (tok)

	{

		tokens[n_delim] = tok;

		tok = _strtok(NULL, delim);

		n_delim++;

	}

	tokens[n_delim] = NULL;



	return (tokens);

}
