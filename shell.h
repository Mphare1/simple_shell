/* By Lunga */
#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>

extern char **environ;

typedef struct shell_env {
	char **path_values;
	char *input;
	char **input_token;
	char *modify_path;
} shell_t;

typedef struct built_in_cmd {
	char *cmd_name;
	void (*cmd)(shell_t *);
} built_t;

int run_build_in(shell_t *, char *);
int run_command(shell_t *, char *, char **);
int run_path(shell_t *, char *);
int check_slash(char *);

/* string.c file*/

size_t _strlen(char *);
char *_strdup(char *);
char **tokenize_str(char *, char *);
int _strcmp(char *, char *);

/* prompt_util.c file*/

void print_ps1(int);
char *find_pathname(char **, char *);
char *_getenv(const char *);
char *make_pathname(char *, char *);
char **get_path(char **);

/* prompt_util2.c file*/

void free_shell_t(shell_t *);

void p_commanderr(char *, char *);

/* buildin.c file */

void my_exit(shell_t *);

void print_env(shell_t *);

/* Function prototypes file*/

char *_strtok(char *, const char *);

ssize_t _getline(char **, size_t *, FILE *);

#endif
