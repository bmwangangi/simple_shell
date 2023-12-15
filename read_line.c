#include "main.h"

/**
 * read_line - used to read the input
 *
 * @i_eof: return the value got
 * Return:string
 */
char *read_line(int *i_eof)
{
	char *userinput = NULL;
	size_t buffersize = 0;

	*i_eof = getline(&userinput, &buffersize, stdin);

	return (userinput);
}
