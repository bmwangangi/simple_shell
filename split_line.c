#include "shell.h"

/**
 * split_string - Tokenizes a string into multiple substrings.
 * @str: The string.
 *
 * Return: a pointer
 */
char **split_string(char *input_str)
{
    /* Initial size of the tokens array */
    int buffer_size = 64;

    /* Counter variable for tokens */
    int token_index = 0;

    /* Allocate memory for the array of pointers to strings */
    char **tokens = malloc(buffer_size * sizeof(char *));

    /* Temporary variable to hold each token */
    char *token;

    /* Check if memory allocation was successful */
    if (!tokens)
    {
        fprintf(stderr, "Error: Failed to allocate memory for tokens in split_line\n");
        exit(EXIT_FAILURE);
    }

    /* Use strtok to tokenize the input string based on a delimiter (TOK_DELIM) */
    token = strtok(input_str, TOK_DELIM);

    /* Loop through the tokens */
    while (token != NULL)
    {
        /* Handle comments: If a token starts with '#', break the loop */
        if (token[0] == '#')
        {
            break;
        }

        /* Store each token in the tokens array */
        tokens[token_index] = token;
        token_index++;

        /* Check if the array needs to be dynamically resized */
        if (token_index >= buffer_size)
        {
            /* Double the size */
            buffer_size += buffer_size;

            /* Reallocate memory */
            tokens = realloc(tokens, buffer_size * sizeof(char *));

            /* Check if reallocation was successful */
            if (!tokens)
            {
                fprintf(stderr, "Error: Failed to reallocate memory for tokens in split_line\n");
                exit(EXIT_FAILURE);
            }
        }

        /* Get the next token */
        token = strtok(NULL, TOK_DELIM);
    }

    /* Add a NULL terminator at the end of the tokens array */
    tokens[token_index] = NULL;

    /* Return the pointer to the array of tokens */
    return tokens;
}
