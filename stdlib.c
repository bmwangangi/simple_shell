#include "main.h"

/**
 * get_len - used to get len
 * @a: data type integer
 * Return: len of no
 */
int get_len(int a)
{
	unsigned int no;
	int len = 1;

	if (a < 0)
	{
		len++;
		no = a * -1;
	}
	else
	{
		no = a;
	}
	while (no > 9)
	{
		len++;
		no = no / 10;
	}

	return (len);
}
/**
 * aux_itoa - for conversion to string
 * @a: interger no
 * Return: Str.
 */
char *aux_itoa(int a)
{
	unsigned int no;
	int len = get_len(a);
	char *buf;

	buf = malloc(sizeof(char) * (len + 1));
	if (buf == 0)
		return (NULL);

	*(buf + len) = '\0';

	if (a < 0)
	{
		no = a * -1;
		buf[0] = '-';
	}
	else
	{
		no = a;
	}

	len--;
	do {
		*(buf + len) = (no % 10) + '0';
		no = no / 10;
		len--;
	}
       	while (no > 0);
	return (buf);
}

/**
 * _atoi - converts to a string
 * @x: the string.
 * Return: int.
 */
int _atoi(char *x)
{
	unsigned int counting = 0, sizing = 0, input = 0, pointer = 1, b = 1, a;

	while (*(x + counting) != '\0')
	{
		if (sizing > 0 && (*(x + counting) < '0' || *(x + counting) > '9'))
			break;

		if (*(x + counting) == '-')
			pointer *= -1;

		if ((*(x + counting) >= '0') && (*(x + counting) <= '9'))
		{
			if (sizing > 0)
				b *= 10;
			sizing++;
		}
		counting++;
	}

	for (a = counting - sizing; a < counting; a++)
	{
		input = input + ((*(x + a) - 48) * b);
		b /= 10;
	}
	return (input * pointer);
}
