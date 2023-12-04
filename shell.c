#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_INPUT_LENGTH 100

/**
 * execute_command - Execute a command with its full path.
 *
 * @command: The command to execute.
 */
void execute_command(const char *command);

/**
 * main - Super simple shell that can run commands with their full path.
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
            printf("\n");
            break; /* EOF (Ctrl+D) or error in input */
        }

        /* Remove trailing newline character */
        size_t input_length = strlen(input);
        if (input_length > 0 && input[input_length - 1] == '\n')
            input[input_length - 1] = '\0';

        /* Check if the user wants to exit */
        if (strcmp(input, "exit") == 0)
            break;

        /* Execute the command */
        execute_command(input);
    }

    return 0;
}

/**
 * execute_command - Execute a command with its full path.
 *
 * @command: The command to execute.
 */
void execute_command(const char *command)
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
        if (execlp(command, command, NULL) == -1)
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
            printf("Child process %d exited with status %d\n", (int)child_pid, WEXITSTATUS(status));
        }
        else
        {
            printf("Child process %d exited abnormally\n", (int)child_pid);
        }
    }
}

