/**
 * File: shell.c
 * Author: BARTASA and  JOE
 * Description: implemantation of a basic simple shell
 */

#include "shell.h"

#define MAX_INPUT_LENGTH 100

/**
 * exe_cmd _ used to execute a commandby the shell
 *
 * @cmd: command to execute.
 */
void exe_cmd(const char *cmd);

/**
 * main - a simple shell
 *
 * Return: Always 0.
 */
int main(void)
{
	char input[MAX_INPUT_LENGTH];

	while (1)
	{
		printf("#cisfun$ ");
		if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
		{
			printf("\n") :
				break;
		}

		size_t input_length = strlen(input);

		if (input_length > 0 && input[input_length - 1] == '\n')
			input[input_length - 1] = '\0';

		if (strcmp(input, "exit") == 0)
			break;

		exe_cmd(input);
	}
	return (0);
}

/**
 * exe_cmd - Execute a command
 *
 * @cmd: command to execute.
 */
void exe_cmd(const char *cmd)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error creating child process");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		/* Code executed by child process */
		if (execlp(cmd, cmd, NULL) == -1)
		{
			perror("Error executing command");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Code executed by the parent process */
		int status;

		if (waitpid(child_pid, &status, 0) == -1)
		{
			perror("Error waiting for child process");
			exit(EXIT_FAILURE);
		}

		if (WIFEXITED(status))
		{
			printf("Child pro %d exited  %d\n", (int)child_pid, WEXITSTATUS(status));
		}
		else
		{
			printf("Child process %d exited abnormally\n", (int)child_pid);
		}
	}
}

