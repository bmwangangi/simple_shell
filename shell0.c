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

/**
 * main - Entry point for the simple shell.
 *
 * Return: Always 0.
 */
int main(void)
{
	char insert[MAX_SIZE];
	int rlt;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("#cisfun$ ");
		}

		/*we use this function to read the user input */
		if (fgets(insert, sizeof(insert), stdin) == NULL)
		{
			if (isatty(STDIN_FILENO))
			{
				printf("\n");
			}

			break;
		}

		insert[strcspn(insert, "\n")] = '\0';

		rlt = exe_cmd(insert);

		if (isatty(STDIN_FILENO))
		{
			if (rlt == 0)
			{
				printf("Command was  successful.\n");
			}
			else
			{
				fprintf(stderr, "./shell: Command failed with status %d\n", rlt);
			}
		}
	}

	return (0);
}

