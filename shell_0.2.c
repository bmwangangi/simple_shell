#include "shell.h"
#include <unistd.h>
#include <sys/wait.h>

/**
 * execute_command - Execute the given command with arguments.
 * @commandTokens: An array of strings where the first element is the command,
 *                 and the rest are arguments.
 */
void execute_command(char **commandTokens)
{
    pid_t childPid = fork();

    if (childPid == -1)
    {
        perror("Error creating child process");
        exit(EXIT_FAILURE);
    }
    else if (childPid == 0)
    {
        /* Code executed by the child process */
        if (execvp(commandTokens[0], commandTokens) == -1)
        {
            perror("Error executing command");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        /* Code executed by the parent process */
        int status;

        if (waitpid(childPid, &status, 0) == -1)
        {
            perror("Error waiting for child process");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status))
        {
            printf("Child process %d exited with status %d\n", (int)childPid, WEXITSTATUS(status));
        }
        else
        {
            printf("Child process %d exited abnormally\n", (int)childPid);
        }
    }
}

/**
 * main - Entry point of the shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
    char userInput[MAX_INPUT_LENGTH];

    while (1)
    {
        printf("#cisfun$ ");
        if (fgets(userInput, MAX_INPUT_LENGTH, stdin) == NULL)
        {
            printf("\n");
            break;
        }

        size_t userInputLength = strlen(userInput);

        if (userInputLength > 0 && userInput[userInputLength - 1] == '\n')
            userInput[userInputLength - 1] = '\0';

        if (strcmp(userInput, "exit") == 0)
            break;

        /* Split the input into tokens (command and arguments) */
        char **commandTokens = split_string(userInput);

        /* Execute the command with arguments */
        execute_command(commandTokens);

        /* Free the allocated memory for tokens */
        free(commandTokens);
    }

    return 0;
}

