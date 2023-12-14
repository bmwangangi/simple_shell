#include "shell.h"

/**
 * **strngtow - splits a string into words.
 * @string: the input string
 * @x: the delimeter string
 * Return: a pointer to an array of strings
 */

char **stringtow(char *string, char *x)
{
	int a, b, c, d, numberwords = 0;
	char **s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!x)
		x = " ";
	for (a = 0; string[a] != '\0'; a++)
		if (!is_delim(string[a], x) && (is_delim(string[a + 1], x) || !string[a + 1]))
			numberwords++;

	if (numberwords == 0)
		return (NULL);
	s = malloc((1 + numberwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numberwords; b++)
	{
		while (is_delim(string[a], x))
			a++;
		c = 0;
		while (!is_delim(string[a + c], x) && string[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[c])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			s[b][d] = string[a++];
		s[b][d] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **stringtow2 - splits syting to words
 * @string: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings
 */
char **strtow2(char *string, char d)
{
	int i, a, b, c, numberwords = 0;
	char **s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (i = 0; string[i] != '\0'; i++)
		if ((string[i] != d && string[i + 1] == d) ||
		    (string[i] != d && !string[i + 1]) || string[i + 1] == d)
			numberwords++;
	if (numberwords == 0)
		return (NULL);
	s = malloc((1 + numberwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, a = 0; a < numberwords; a++)
	{
		while (string[i] == d && string[i] != d)
			i++;
		b = 0;
		while (string[i + b] != d && string[i + b] && string[i + b] != d)
			b++;
		s[a] = malloc((b + 1) * sizeof(char));
		if (!s[b])
		{
			for (b = 0; b < a; b++)
				free(s[b]);
			free(s);
			return (NULL);
		}
		for (c = 0; c < b; c++)
			s[b][c] = string[i++];
		s[a][c] = 0;
	}
	s[a] = NULL;
	return (s);
}
