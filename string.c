#include "shell.h"
#include <string.h>



/**
  * ..................
  * ..................
  * ..................
  */
size_t _strlen(char *str)

{
char *local_str = str;
size_t c_fd = 0;

	if (str == NULL)

		return (c_fd);

	while (*local_str++ != '\0')

		c_fd++;

	return (c_fd);

}



/**
 * ...................
 * ...................
 *
 * ..................
 * ..................
 */
char *_strdup(char *s)

{

size_t xz =0;
size_t t_l = 0;

char *delis;

	t_l = _strlen(s);

	delis = malloc(sizeof(char) * (t_l + 1));

	if (!delis)

		return (NULL);

	while (s[xz])

	{

		delis[xz] = s[xz];

		xz++;

	}

	delis[xz] = '\0';



	return (delis);

}

/**
  * ..................
  * ..................
  * ..................
  */

int _strcmp(char *str1, char *str2)

{

	while (*str1 != '\0' && *str2 != '\0')

	{

		if (*str1++ != *str2++)

			return (1);

	}

	if (*str1 == '\0' && *str2 == '\0')

		return (0);

	return (1);

}

/**
 * .....................
 * .....................
 *......................
 * Return: ............
 */


char **tokenize_str(char *str, char *delim)

{

	size_t n_del2 = 0;
	char *strc_del2, *tok_1;
	char **tokss;
	if (!str || !delim)

		return (NULL);

	strc_del2 = _strdup(str);
	tok_1 = _strtok(strc_del2, delim);

	while (tok_1)

	{

	n_del2++;
	tok_1 = _strtok(NULL, delim);

	}

	free(strc_del2);
	tokss = malloc(sizeof(char *) * (n_del2 + 1));

	if (!tokss)

		return (NULL);

	tok_1 = _strtok(str, delim);

	n_del2 = 0;

	while (tok_1)

	{

		tokss[n_del2] = tok_1;
		tok_1 = _strtok(NULL, delim);

		n_del2++;

	}

	tokss[n_del2] = NULL;
	return (tokss);

}