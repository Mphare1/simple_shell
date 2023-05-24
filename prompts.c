#include "main.h"

/**
 * free_shell_t - Free memory allocated for the shell_t structure
 * @shell_ptrs: Pointer to the shell_t structure
 */
void free_shell_t(shell_t *shell_ptrs)
{
	free(shell_ptrs->path_values);
	free(shell_ptrs->input);
	free(shell_ptrs->input_token);
	free(shell_ptrs->modify_path);
}


/**
 * p_commanderr - Print error message for command not found
 * @command: The command that was not found
 * @filename: The filename associated with the command
 */
void p_commanderr(char *command, char *filename)
{
	char *err_msg;
	char *err = ": command not found\n";
	size_t num_char, i = 0;
	(void)filename;

	num_char = _strlen(err) + _strlen(command);

	err_msg = malloc(sizeof(char) * (num_char + 1));

	if (err_msg == NULL)
	{
		/* Handle memory allocation error */
		/* Print an error message or take appropriate action */
		return;
	}

	while (*command != '\0')
		err_msg[i++] = *command++;

	while (*err != '\0')
		err_msg[i++] = *err++;

	err_msg[i] = '\0';

	write(STDERR_FILENO, err_msg, num_char);

	free(err_msg);
}
/**
 * print_ps1 - Print the PS1 prompt
 * @num: Flag indicating the presence of an error
 */
void print_ps1(int num)
{
	char ppp[] = "MARSU$ ";
	
	size_t length_ppp;
	
	int o_err;

	o_err = errno;
	length_ppp = _strlen(ppp);

	if (isatty(STDIN_FILENO))
		
		write(STDOUT_FILENO, ppp, length_ppp);

	if (num == 0)
		errno = 0;
	else
		errno = o_err;
}


/**
 * get_path - Get the PATH directories as tokens
 * @_delimt: The delimiter to split the PATH string
 * @modify_path: Pointer to store the modified PATH string
 *
 * Return: Pointer to the array of tokens
 */
char **get_path(char **modify_path)
{
	char **token_ptr;
	char *path, *_delimt;
	unsigned int i, j, num_char;

	_delimt = ":";
	path = _getenv("PATH");
	num_char = _strlen(path);

	*modify_path = malloc(sizeof(char) * (num_char + 2));
	if (num_char == 0)
	{
		(*modify_path)[0] = '.';
		(*modify_path)[1] = '\0';
	}
	else
	{
		i = 0;
		j = 0;
		while (path[i] != '\0')
		{
			if (i == 0 && path[i] == ':')
			{
				(*modify_path)[j++] = '.';
				(*modify_path)[j++] = path[i];
			}
			else if (i == num_char - 1 && path[i] == ':')
			{
				(*modify_path)[j++] = path[i];
				(*modify_path)[j++] = '.';
			}
			else if (path[i] == ':' && path[i + 1] == ':')
			{
				(*modify_path)[j++] = path[i];
				(*modify_path)[j++] = '.';
			}
			else
			{
				(*modify_path)[j++] = path[i];
			}
			i++;
		}

		while (j < num_char + 2)
		{
			(*modify_path)[j++] = '\0';
		}
	}

	token_ptr = tokenize_str(*modify_path, _delimt);

	return (token_ptr);
}

/**
 * find_pathname - Find the full pathname of a file in the given paths
 * @folder: Array of paths to search for the file
 * @input: Name of the file to find
 *
 * Return: Pointer to the full pathname of the file, or NULL if not found
 */
char *find_pathname(char **folder, char *input)
{
	unsigned int i;
	DIR *directory;
	struct dirent *filename;
	int s_cmp, matched;
	char *result;

	filename = NULL;
	matched = 0;

	for (i = 0; folder[i] != NULL; i++)
	{
		directory = opendir(folder[i]);

		if (directory == NULL)
		{
			errno = EBADF;
			return (NULL);
		}

		while ((filename = readdir(directory)) != NULL)
		{
			s_cmp = _strcmp(filename->d_name, input);

			if (s_cmp == 0)
			{
				matched = 1;
				break;
			}
		}

		if (matched == 1)
			break;

		closedir(directory);
	}

	if (matched == 1)
	{
		result = make_pathname(folder[i], input);

		if (access(result, R_OK) != -1)
			errno = EACCES;

		closedir(directory);
		return (result);
	}

	errno = EBADF;
	return (NULL);
}
/**
 * make_pathname - Concatenate a path and a file to create a full pathname
 * @_path: The path component
 * @_file: The file component
 *
 * Return: Pointer to the concatenated pathname, or NULL on failure
 */
char *make_pathname(char *_path, char *_file)
{
	size_t num_path, num_file;
	char *resull;
	unsigned int x, y;

	num_path = _strlen(_path);
	num_file = _strlen(_file);

	resull = malloc(sizeof(char) * (num_path + num_file + 2));
	if (resull == NULL)
		return (NULL);

	for (x = 0; x < num_path; x++)
		resull[x] = _path[x];

	resull[x++] = '/';

	for (y = 0; y < num_file; y++)
		resull[x + y] = _file[y];

	resull[x + y] = '\0';

	return (resull);
}

/**

  * _getenv - gets the value of the environment variable

  * @name: variable to find

  * Return: pointer to the value of the environment variable.

  */

char *_getenv(const char *name)

{

	unsigned int i, j;



	for (i = 0; environ[i] != NULL; i++)

	{

		for (j = 0; environ[i][j] != '=' && environ[i][j] == name[j] && name[j]; j++)

			;

		if (environ[i][j] == '=' && name[j] == '\0')

			return (&environ[i][++j]);

	}

	return (NULL);

}
