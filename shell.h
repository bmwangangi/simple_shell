#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100
#define TOK_DELIM " \t\r\n\a"

char **split_string(char *input_str);
void exe_cmd(const char *cmd);
char *simple_readline(void);

#endif
