#include "main.h"

/**
 * main - Entry point of the program
 * @argc: The number of command-line arguments
 * @argv: An array of command-line arguments
 * @envp: An array of environment variables
 *
 * Return: The exit status of the program
 */
int main(int argc, char *argv[], char *envp[])
{
	char **val_, *md_path, **i_tkk, *_input;
	char delimiter[] = " \n\r\t";
	size_t _inp2;
	ssize_t l_stats;
	shell_t shell_pts;

	(void)argc;
	_input = NULL;
	val_ = get_path(&md_path);
	print_ps1(0);
	shell_pts.modify_path = md_path;
	shell_pts.path_values = val_;
	signal(SIGINT, SIG_IGN);
	while ((l_stats = getline(&_input, &_inp2, stdin)) != -1)
	{
		shell_pts.input = _input;
		i_tkk = tokenize_str(_input, delimiter);
		shell_pts.input_token = i_tkk;
		if (i_tkk[0] && check_slash(i_tkk[0]) == 1)
			run_path(&shell_pts, argv[0]);
		else if (i_tkk[0] && check_slash(i_tkk[0]) == 0)
		{
			if (run_build_in(&shell_pts, argv[0]) == 1)
				run_command(&shell_pts, argv[0], envp);
		}
		free(i_tkk);
		print_ps1(1);
	}
	free(md_path);
	free(val_);
	free(_input);
	return (errno);
}


/**
 * check_slash - Check if a string contains a slash character ('/')
 * @str: The input string
 *
 * Return: 1 if the string contains a slash, 0 otherwise
 */
int check_slash(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '/')
			return (1);
	}

	return (0);
}


/**
  * run_command - runs the command given by the user
  * @shell_ptrs: structure containing all malloced spaces
  * @filename: name of the file being run
  * @envp: environment variable
  * Return: errno value
  */
int run_command(shell_t *shell_ptrs, char *filename, char **envp)
{
	pid_t child_pid;
	char **input_token = shell_ptrs->input_token;
	char **path = shell_ptrs->path_values;
	char *input_org;
	int status;

	if (input_token[0] != NULL)
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			input_org = _strdup(input_token[0]);
			input_token[0] = find_pathname(path, input_token[0]);
			if (input_token[0] != NULL)
			{
				if (execve(input_token[0], input_token, envp) == -1)
					perror(filename);
				free(input_token[0]);
			}
			else
			{
				errno = 127;
				p_commanderr(input_org, filename);
			}
			free_shell_t(shell_ptrs);
			free(input_org);
			_exit(errno);
		}
		else
			wait(&status);
	}
	errno = status % 255;
	return (errno);
}

/**
 * run_build_in - checks if the the user calls a built-in cmd.
 * @ptrs: contains all the malloced spaces.
 * @filename: name of the file
 * Return: 1 for match not found, 0 for match found.
 */
int run_build_in(shell_t *ptrs, char *filename)
{
	size_t index;
	unsigned int num_words;
	char **input_words;
	built_t cmd[] = {
		{"exit", my_exit},
		{"env", print_env},
		{NULL, NULL},
	};

	(void)filename;
	if (!ptrs)
		return (1);
	if (!(ptrs->input_token[0]))
		return (1);

	input_words = ptrs->input_token;
	num_words = 0;
	while (input_words[num_words] != NULL)
		num_words++;
	index = 0;
	while (cmd[index].cmd_name)
	{
		if (!_strcmp(ptrs->input_token[0], cmd[index].cmd_name))
		{
			(cmd[index].cmd)(ptrs);
			return (0);
		}
		index++;
	}
	return (1);
}

/**
  * run_path - runs the command specified by the pathname
  * @shell_ptrs: structure containing all malloced memory
  * @filename: filename of the file
  * Return: still to be determined
  */
int run_path(shell_t *shell_ptrs, char *filename)
{
	pid_t child_pid;
	int status;
	char **input_token = shell_ptrs->input_token;

	child_pid = fork();
	if (child_pid == 0)
	{
		if (execve(input_token[0], input_token, environ) == -1)
			perror(filename);
		free_shell_t(shell_ptrs);
		_exit(errno);
	}
	else
		wait(&status);
	errno = status % 255;
	return (errno);
}
