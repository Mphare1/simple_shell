#include "shell.h"



/**
  * ************************
  * ************************
  */

void free_shell_t(shell_t *shell_ptrs)
{
	free(shell_ptrs->path_values);
	free(shell_ptrs->input);
	free(shell_ptrs->input_token);
	free(shell_ptrs->modify_path);
}
/**
  * *******************************************
  * *******************************************
  * *******************************************
  */

void p_commanderr(char *cmnd, char *file_name)
{
size_t len_char = _strlen(err_) + _strlen(cmnd);
char *err_msgs = malloc(sizeof(char) * (++len_char));;
char *err_ = ": not found\n";
size_t j = 0;
(void)file_name;

	while (*cmnd != '\0')

		err_msgs[j++] = *cmnd++;

	while (*err_ != '\0')

		err_msgs[j++] = *err_++;

	err_msgs[j] = '\0';

	write(STDERR_FILENO, err_msgs, len_char);

	free(err_msgs);

}
