#include "main.h"

/**
 * read_line - used to read the input from a string
 *
 * @i_eof: return value
 * Return: str
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}
