#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


extern char **environ;  /* Declare the external variable */

#define MAX_INPUT_SIZE 1024

/**
 * execute_command - Executes a command in a child process.
 * @cmd: The command to be executed.
 *
 * Return: The exit status of the executed command.
 */
int execute_command(char *cmd) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        /* Child process */
        char **args = malloc(2 * sizeof(char *));
        if (args == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        args[0] = cmd;
        args[1] = NULL;

        if (execve(cmd, args, environ) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }

        free(args);
    } else {
        /* Parent process */
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
    }

    return -1;
}

/**
 * main - Entry point for the simple shell.
 *
 * Return: Always returns 0.
 */
int main(void) {
    char input[MAX_INPUT_SIZE];
    int result;

    while (1) {
        printf("#cisfun$ ");

        /* Read user input */
        if (fgets(input, sizeof(input), stdin) == NULL) {
            /* Handle Ctrl+D (end of file) */
            printf("\n");
            break;
        }

        /* Remove trailing newline character */
        input[strcspn(input, "\n")] = '\0';

        /* Execute the command */
        result = execute_command(input);

        if (result == 0) {
            printf("Command executed successfully.\n");
        } else {
            fprintf(stderr, "./shell: No such file or directory\n");
        }
    }

    return 0;
}
