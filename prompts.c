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

  * find_pathname - finds the pathname attached to the associated command

  * @path: pointer to 2d array of tokenized directories in PATH

  * @input: input to find

  * Return: Path to the input file.

  */

char *find_pathname(char **path, char *input)

{

	unsigned int i;

	DIR *directory;

	struct dirent *filename;

	int str_cmp, match_found;

	char *result;



	filename = NULL;

	match_found = 0;

	for (i = 0; path[i] != NULL; i++)

	{

		directory = opendir(path[i]);

		if (directory == NULL)

		{

			errno = EBADF;

			return (NULL);

		}

		while ((filename = readdir(directory)) != NULL)

		{

			/* TODO make strcmp function */

			str_cmp = _strcmp(filename->d_name, input);

			if (str_cmp == 0)

			{

				match_found = 1;

				break;

			}

		}

		if (match_found == 1)

			break;

		closedir(directory);

	}

	if (match_found == 1)

	{

		result = make_pathname(path[i], input);

		if (access(result, R_OK) != -1)

			errno = EACCES;

		closedir(directory);

		return (result);

	}

	errno = EBADF;

	return (NULL);

}



/**

  * make_pathname - takes result from path_name and creates a string.

  * string contains the full pathname.

  * @path: pathname

  * @file: file in the path

  * Return: pointer to an allocated string that contains the full pathname.

  */

char *make_pathname(char *path, char *file)

{

	size_t num_path, num_file;

	char *result;

	unsigned int j, k;



	num_path = _strlen(path);

	num_file = _strlen(file);

	result = malloc(sizeof(char) * (num_path + num_file + 2));

	if (result == NULL)

		return (NULL);

	for (j = 0; j < num_path; j++)

		result[j] = path[j];

	result[j++] = '/';

	for (k = 0; k < num_file; k++)

		result[j + k] = file[k];

	result[j + k] = '\0';

	return (result);

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
