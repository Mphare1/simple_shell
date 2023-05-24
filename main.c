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
 * run_command - Run a command by executing it as a child process
 * @shell_ptrs: Pointer to the shell_t structure
 * @filename: Name of the current file
 * @envp: Array of environment variables
 *
 * Return: The error number
 */
int run_command(shell_t *shell_pts, char *filename, char **envp)
{
	pid_t c_pid;
	char **i_ttk = shell_pts->input_token;
	char **_path = shell_pts->path_values;
	char *i_gg;
	int stats;

	if (i_ttk[0] != NULL)
	{
		c_pid = fork();
		if (c_pid == 0)
		{
			i_gg = _strdup(i_ttk[0]);
			i_ttk[0] = find_pathname(_path, i_ttk[0]);
			if (i_ttk[0] != NULL)
			{
				if (execve(i_ttk[0], i_ttk, envp) == -1)
					perror(filename);
				free(i_ttk[0]);
			}
			else
			{
				errno = 127;
				p_commanderr(i_gg, filename);
			}
			free_shell_t(shell_pts);
			free(i_gg);
			_exit(errno);
		}
		else
			wait(&stats);
	}
	errno = stats % 255;
	return (errno);
}

/**
 * run_build_in - Check and run built-in commands
 * @ptrs: Pointer to the shell_t structure
 * @filename: Name of the current file
 *
 * Return: 0 if a built-in command is executed, 1 otherwise
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
	for (; input_words[num_words] != NULL; num_words++)
		;

	index = 0;
	for (; cmd[index].cmd_name; index++)
	{
		if (!_strcmp(ptrs->input_token[0], cmd[index].cmd_name))
		{
			(cmd[index].cmd)(ptrs);
			return (0);
		}
	}
	return (1);
}


/**
 * run_path - Execute a command with absolute/relative path
 * @shell_ptrs: Pointer to the shell_t structure
 * @filename: Name of the current file
 *
 * Return: The error number
 */
int run_path(shell_t *shell_ptrs, char *filename)
{
	pid_t c_pif;
	int stats;
	char **_itoks = shell_ptrs->input_token;

	c_pif = fork();
	if (c_pif == 0)
	{
		if (execve(_itoks[0], _itoks, environ) == -1)
			perror(filename);
		free_shell_t(shell_ptrs);
		_exit(errno);
	}
	else
		wait(&stats);
	errno = stats % 255;
	return (errno);
}
