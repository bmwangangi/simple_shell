#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_SIZE 1024

/**
 * exe_cmd - used to execute the commands
 * @command:the cmd to be executed
 *
 * Return: Exit status
 */
int exe_cmd(char *command)
{
	int situation = system(command);

	if (situation == -1)
	{
		perror("method");
		exit(EXIT_FAILURE);
	}

	return (situation);
}
