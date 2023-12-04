#include <stdio.h>
#include <stdlib.h>

/* Define constant for maximum command length */
#define MAX_COMMAND_LENGTH 100

/**
 * main - Entry point of the program
 *
 * Description: This program prompts the user for input, reads the input,
 * and prints each entered command on the next line.
 *
 * Return: Always 0 (success)
 */
int main(void)
{
    char *input = NULL; /* Buffer to store user input */
    size_t length = 0;  /* Length of the input buffer */
    ssize_t return_value; /* Return value of the getline function */

    while (1)
    {
        printf("$ ");

        /* Read input from the user */
        return_value = getline(&input, &length, stdin);

        /* Check for errors or end-of-file */
        if (return_value == -1)
        {
            break; /* Exit the loop on error */
        }

        /* Check for end-of-file (Ctrl+D) */
        if (return_value == 0)
        {
            printf("\n");
            break; /* Exit the loop on end-of-file */
        }

        /* Print the entered command */
        printf("%s", input);
    }

    /* Free allocated memory */
    free(input);

    return 0;
}

