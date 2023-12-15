#include "main.h"

/**
 * read_line - used to read the input
 *
 * @r_lin: return the value got
 * Return:string
 */
char *read_line(int *r_lin)
{
	char *userinput = NULL;
	size_t buffersize = 0;

	*r_lin = getline(&userinput, &buffersize, stdin);

	return (userinput);
}
