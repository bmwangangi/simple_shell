#include "shell.h"

/**
 *_inputs - prints the input
 * @str: the represented of the string
 *
 * Return: NULL
 */
void _inputs(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_eputchar(str[a]);
		a++;
	}
}

/**
 * _inputchar - writes a into standard error
 * @a: The the chasracter we are watching
 *
 * Return: On success 1.
 */
int _inputchar(char a)
{
	static int b;
	static char buf[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || b >= WRITE_BUF_SIZE)
	{
		write(2, buf, b);
		b = 0;
	}
	if (a != BUF_FLUSH)
		buf[b++] = a;
	return (1);
}

/**
 * _putingfd - writes the a character in to a given fd
 * @a: The characterwe are dealing with
 * @fd: The filedescriptor
 *
 * Return: On success 1.
 */
int _putfd(char a, int fd)
{
	static int b;
	static char buf[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || b >= WRITE_BUF_SIZE)
	{
		write(fd, buf, b);
		b = 0;
	}
	if (a != BUF_FLUSH)
		buf[b++] = a;
	return (1);
}

/**
 *_printfd - prints the string we inputed
 * @str: the string
 * @fd: the filedescriptor
 *
 * Return: the number of output
 */
int _putsfd(char *str, int fd)
{
	int a = 0;

	if (!str)
		return (0);
	while (*str)
	{
		a += _putfd(*str++, fd);
	}
	return (a);
}
