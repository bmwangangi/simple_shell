#include "main.h"

/**
 * get_len - used to get len
 * @n: data type integer
 * Return: len of no
 */
int get_len(int n)
{
	unsigned int no;
	int len = 1;

	if (n < 0)
	{
		len++;
		no = n * -1;
	}
	else
	{
		no = n;
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
 * @n: interger no
 * Return: Str.
 */
char *aux_itoa(int n)
{
	unsigned int no;
	int len = get_len(n);
	char *buf;

	buf = malloc(sizeof(char) * (len + 1));
	if (buf == 0)
		return (NULL);

	*(buf + len) = '\0';

	if (n < 0)
	{
		no = n * -1;
		buf[0] = '-';
	}
	else
	{
		no = n;
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
 * @s: the string.
 * Return: int.
 */
int _atoi(char *s)
{
	unsigned int counting = 0, sizing = 0, input = 0, pointer = 1, b = 1, a;

	while (*(s + counting) != '\0')
	{
		if (sizing > 0 && (*(s + counting) < '0' || *(s + counting) > '9'))
			break;

		if (*(s + counting) == '-')
			pointer *= -1;

		if ((*(s + counting) >= '0') && (*(s + counting) <= '9'))
		{
			if (sizing > 0)
				b *= 10;
			sizing++;
		}
		counting++;
	}

	for (a = counting - sizing; a < counting; a++)
	{
		input = input + ((*(s + a) - 48) * b);
		b /= 10;
	}
	return (input * pointer);
}
