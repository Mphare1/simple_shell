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
 * tokenize_str - Tokenize a string based on delimiters
 * @str: The string to tokenize
 * @delim: The delimiter string
 *
 * Return: Array of tokens, or NULL on failure
 */
char **tokenize_str(char *str, char *delim)
{
	size_t _delimit = 0;
	char *cpyy, *tok;
	char **_ttk;

	if (!str || !delim)
		return NULL;

	cpyy = _strdup(str);

	/* Count the delimiters */
	tok = _strtok(cpyy, delim);
	while (tok)
	{
		_delimit++;
		tok = _strtok(NULL, delim);
	}

	/* Free the cpyy */
	free(cpyy);

	/* Allocate memory for tokens based on _delimit + 1 for the NULL */
	_ttk = malloc(sizeof(char *) * (_delimit + 1));
	if (!_ttk)
		return NULL;

	/* Tokenize str */
	tok = _strtok(str, delim);
	_delimit = 0;
	while (tok)
	{
		_ttk[_delimit] = tok;
		tok = _strtok(NULL, delim);
		_delimit++;
	}

	_ttk[_delimit] = NULL;

	return _ttk;
}
