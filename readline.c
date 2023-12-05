#include "shell.h"

/**
 * simple_readline - used to read from standard inpur or output
 *
 * Return: Pointer to a string.
 */
char *simple_readline(void);

int main(void)
{
    printf("Enter a line: ");
    char *input_line = simple_readline();
    printf("You entered: %s\n", input_line);

    free(input_line);

    return 0;
}
char *simple_readline(void)
{
    char *user_input = NULL;
    size_t buffer_size = 0;
    int getline_result;

    while ((getline_result = getline(&user_input, &buffer_size, stdin)) == -1)
    {
        /* If getline fails */
        if (feof(stdin))
        {
            free(user_input);       
            exit(EXIT_SUCCESS);      
        }
        else
        {
            /* If there's an error while reading the line */
            free(user_input);
            perror("Error reading the line from stdin");
            exit(EXIT_FAILURE);
        }
    }

    return user_input;
}

