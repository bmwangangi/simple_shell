#include <shell.h>

#define TOK_DELIM " \t\r\n\a"  /* Example delimiter, you can customize this */

int main(void)
{
    char input_str[] = "Hello World bartasa needs to know how you are?";  /* Example input string */
    char **tokens = split_string(input_str);

    /* Print the tokens */
    for (int i = 0; tokens[i] != NULL; i++)
    {
        printf("Token %d: %s\n", i + 1, tokens[i]);
    }

    /* Free the allocated memory */
    free(tokens);

    return 0;
}

