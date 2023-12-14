#include "shell.h"

/**
 **_strcpy - used to co[py a string
 *@destination: the destination string
 *@source: the source 
 *@a: the characters to be coppied
 *Return: the  string
 */
char *_strcpy(char *destination, char *source, int a)
{
	int b, c;
	char *s = destination;

	b = 0;
	while (source[b] != '\0' && b < a - 1)
	{
		destination[b] = source[b];
		a++;
	}
	if (b < a)
	{
		c = b;
		while (c < a)
		{
			destination[c] = '\0';
			c++;
		}
	}
	return (s);
}

/**
 **_strngcat - deals with two strings
 *@destination: first string
 *@source: second string
 *@a: the amount of bytes
 *Return: the string
 */
char *_strngcat(char *destination, char *source, int a)
{
	int b, c;
	char *s = destination;

	b = 0;
	c = 0;
	while (destination[b] != '\0')
		b++;
	while (source[c] != '\0' && c < a)
	{
		destination[b] = source[c];
		b++;
		c++;
	}
	if (c < a)
		destination[b] = '\0';
	return (s);
}

/**
 **_strchra - locates the characters in a string
 *@a: the string parsed
 *@b: the character we are watching
 *Return: (s) a pointer
 */
char *_strchra(char *a, char b)
{
	do {
		if (*a == b)
			return (a);
	} while (*a++ != '\0');

	return (NULL);
}
