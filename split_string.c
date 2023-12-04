#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100

/**
 * split_string - Splits a string into words.
 * @input: The input string to be split.
 * @num_words: A pointer to an integer to store the number of words.
 *
 * Return: An array of strings containing the words.
 */
char **split_string(const char *input, int *num_words);

/**
 * main - Entry point of the program.
 *
 * Description: This program demonstrates the split_string function by
 * splitting an example string into words and printing the result.
 *
 * Return: Always 0 (success).
 */
int main(void)
{
    const char *input_string = "Hello World! This is a sample string.";

    int num_words;
    char **words_array = split_string(input_string, &num_words);

    printf("Number of words: %d\n", num_words);
    printf("Words:\n");

    for (int i = 0; i < num_words; i++) {
        printf("%s\n", words_array[i]);
        free(words_array[i]); /* Free each word */
    }

    free(words_array); /* Free the array of words */

    return 0;
}

char **split_string(const char *input, int *num_words)
{
    char **words_array = malloc(MAX_WORDS * sizeof(char *));
    if (words_array == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    char *token;
    char *input_copy = strdup(input); /* Create a copy of the input string */
    if (input_copy == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    *num_words = 0;

    /* Tokenize the copy string using strtok */
    token = strtok(input_copy, " \t\n");

    while (token != NULL) {
        /* Allocate memory for each word and copy the token */
        words_array[*num_words] = strdup(token);
        if (words_array[*num_words] == NULL) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        (*num_words)++;

        /* Get the next token */
        token = strtok(NULL, " \t\n");

        if (*num_words >= MAX_WORDS) {
            fprintf(stderr, "Exceeded the maximum number of words\n");
            exit(EXIT_FAILURE);
        }
    }

    free(input_copy); /* Free the copy of the input string */

    return words_array;
}

