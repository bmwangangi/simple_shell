#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATH_LENGTH 4096

/**
 * findFileInPath - Search for a file in the PATH and print its full path.
 *
 * @filename: The name of the file to search for.
 */
void findFileInPath(const char *filename);

/**
 * main - Entry point of the program.
 *
 * @argc: The number of command-line arguments.
 * @argv: An array of strings representing the command-line arguments.
 *
 * Return: 0 on success, 1 on failure.
 */
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s filename ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        findFileInPath(argv[i]);
    }

    return 0;
}

/**
 * findFileInPath - Search for a file in the PATH and print its full path.
 *
 * @filename: The name of the file to search for.
 */
void findFileInPath(const char *filename)
{
    const char *path = getenv("PATH");
    char *pathCopy = NULL;
    char *pathToken;

    if (path == NULL)
    {
        fprintf(stderr, "PATH environment variable not set\n");
        exit(EXIT_FAILURE);
    }

    pathCopy = strdup(path);
    if (pathCopy == NULL)
    {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    pathToken = strtok(pathCopy, ":");
    while (pathToken != NULL)
    {
        char fullPath[MAX_PATH_LENGTH];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", pathToken, filename);

        if (access(fullPath, F_OK) == 0)
        {
            printf("%s\n", fullPath);
            free(pathCopy);
            return;
        }

        pathToken = strtok(NULL, ":");
    }

    printf("%s not found in PATH\n", filename);
    free(pathCopy);
}

