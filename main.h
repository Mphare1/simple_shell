#ifndef MAIN_H
#define MAIN_H

extern char **environ;

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

typedef struct shell_env
{
	char **path_values;
	char *input;
	char **input_token;
	char *modify_path;
} shell_t;

typedef struct built_in_cmd
{
	char *cmd_name;
	void (*cmd)(shell_t *);
} built_t;

/* main.c file functions*/
int run_build_in(shell_t *, char *);
int run_command(shell_t *, char *, char **);
int run_path(shell_t *, char *);
int check_slash(char *);

/* string.c functions*/
size_t _strlen(char *);
char *_strdup(char *);
char **tokenize_str(char *, char *);
int _strcmp(char *, char *);

/* prompts.c */
void print_ps1(int);
char *find_pathname(char **, char *);
char *_getenv(const char *);
void free_shell_t(shell_t *);
void p_commanderr(char *, char *);
char *make_pathname(char *, char *);
char **get_path(char **);


/* build.c functions*/
void my_exit(shell_t *);
void print_env(shell_t *);

/* stok.c functions*/
char *_strtok(char *, const char *);
ssize_t getline(char **, size_t *, FILE *);

#endif
