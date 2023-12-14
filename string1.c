#include "shell.h"

/**
 * _stringcpy - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *_stringcpy(char *destination, char *source)
{
	int a = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[a])
	{
		destination[a] = source[a];
		a++;
	}
	destination[a] = 0;
	return (destination);
}

/**
 * _stringdup - duplicates a string
 * @string: the string to duplicate
 *
 * Return: pointer
 */
char *_stringdup(const char *string)
{
	int len = 0;
	char *ret;

	if (string == NULL)
		return (NULL);
	while (*string++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--string;
	return (ret);
}

/**
 *_inputs - prints an input string
 *@string: the string to be printed
 *
 * Return: Nothing
 */
void _inputs(char *string)
{
	int a = 0;

	if (!string)
		return;
	while (string[a] != '\0')
	{
		_putchar(string[a]);
		a++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @a: The character
 *
 * Return: On success 1.
 */
int _putchar(char a)
{
	static int b;
	static char buf[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || b >= WRITE_BUF_SIZE)
	{
		write(1, buf, b);
		b = 0;
	}
	if (a != BUF_FLUSH)
		buf[b++] = a;
	return (1);
}
