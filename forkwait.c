#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * execute_ls - Execute the command "ls -l /tmp" using execve.
 */
void execute_ls(void);

/**
 * main - Create 5 child processes, execute "ls -l /tmp" in each child, and wait for them.
 *
 * Return: Always 0.
 */
int main(void)
{
    for (int a = 0; a < 5; ++a)
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
            execute_ls();
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

    return 0;
}

/**
 * execute_ls - Execute the command "ls -l /tmp" using execve.
 */
void execute_ls(void)
{
    char *command = "/bin/ls";
    char *args[] = {command, "-l", "/tmp", NULL};

    if (execve(command, args, NULL) == -1)
    {
        perror("Error executing execve");
        exit(EXIT_FAILURE);
    }

    /* Note: The code below will only be executed if execve fails */
    exit(EXIT_FAILURE);
}

