#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

extern char **environ;
void display_prompt(void);
char *read_input();
char **tokenize_input(char *input_line);
void execute_command(char **arguments, int *exit_status);
int is_builtin_command(char **arguments);
void handle_signal(int signal_number);

#endif
