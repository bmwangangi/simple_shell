#include "shell.h"

/**
 * exit_builtin - works as the exit built in
 *
 * Return: 0
 */
int exit_builtin(void)
{
    exit(EXIT_SUCCESS);
}

/**
 * is_it_exit_builtin - Checks if its exit
 * @cmd: The command
 *
 * Return: 1
 */
int is_it_exit_builtin(char *cmd)
{
    return strcmp(cmd, "exit") == 0;
}

