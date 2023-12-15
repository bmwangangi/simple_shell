#include "main.h"

/**
 * bring_line - used to  assign a line to a character
 * @linepointer: used to store the input
 * @buf: the string called
 * @b: the line size
 * @c: the buffer
 */
void bring_line(char **linepointer, size_t *b, char *buf, size_t c)
{

	if (*linepointer == NULL)
	{
		if  (c > BUFSIZE)
			*b = c;

		else
			*b = BUFSIZE;
		*linepointer = buf;
	}
	else if (*b < c)
	{
		if (c > BUFSIZE)
			*b = c;
		else
			*b = BUFSIZE;
		*linepointer = buf;
	}
	else
	{
		_strcpy(*linepointer, buf);
		free(buf);
	}
}
/**
 * get_line - used to read input
 * @linepointer: where it is stored
 * @b: klength of the line input
 * @see: where to read from
 * Return: no of bytes
 */
ssize_t get_line(char **linepointer, size_t *x, FILE *see)
{
	int a;
	static ssize_t userinput;
	ssize_t retvalue;
	char *buffers;
	char b = 'z';

	if (userinput == 0)
		fflush(see);
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
	bring_line(linepointer, x, buffers, userinput);
	retvalue = userinput;
	if (a != 0)
		userinput = 0;
	return (retvalue);
}
