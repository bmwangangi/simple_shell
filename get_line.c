#include "main.h"

/**
 * bring_line - used to  assign a line to a character
 * @lineptr: used to store the input
 * @buffer: the string called
 * @n: the line size
 * @j: the buffer
 */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * get_line - used to read input
 * @lineptr: where it is stored
 * @n: klength of the line input
 * @stream: where to read from
 * Return: no of bytes
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int a;
	static ssize_t userinput;
	ssize_t retvalue;
	char *buffers;
	char b = 'z';

	if (userinput == 0)
		fflush(stream);
	else
		return (-1);
	userinput = 0;

	buffers = malloc(sizeof(char) * BUFSIZE);
	if (buffers == 0)
		return (-1);
	while (b != '\n')
	{
		a = read(STDIN_FILENO, &b, 1);
		if (a == -1 || (a == 0 && userinput == 0))
		{
			free(buffers);
			return (-1);
		}
		if (a == 0 && userinput != 0)
		{
			userinput++;
			break;
		}
		if (userinput >= BUFSIZE)
			buffers = _realloc(buffers, userinput, userinput + 1);
		buffers[userinput] = b;
		userinput++;
	}
	buffers[userinput] = '\0';
	bring_line(lineptr, n, buffers, userinput);
	retvalue = userinput;
	if (a != 0)
		userinput = 0;
	return (retvalue);
}
