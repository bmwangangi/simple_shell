#include "main.h"

/**
 * _strdup - duplicates a str in the heap memory.
 * @string: Type char pointer str
 * Return: duplicated str
 */
char *_strdup(const char *string)
{
	char *new;
	size_t len;

	len = _strlen(string);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcpy(new, string, len + 1);
	return (new);
}

/**
 * _strlen - Returns the lenght of a string.
 * @string: Type char pointer
 * Return: Always 0.
 */
int _strlen(const char *string)
{
	int len;

	for (len = 0; string[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * cmp_chars - compare chars of strings
 * @string: input string.
 * @trab: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int cmp_chars(char string[], const char *trab)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; string[i]; i++)
	{
		for (j = 0; trab[j]; j++)
		{
			if (string[i] == trab[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _strtok - splits a string by some delimiter.
 * @string: input string.
 * @trab: delimiter.
 *
 * Return: string splited.
 */
char *_strtok(char string[], const char *trab)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (string != NULL)
	{
		if (cmp_chars(string, trab))
			return (NULL);
		splitted = string;
		i = _strlen(string);
		str_end = &string[i];
	}
	str_start = splitted;
	if (str_start == str_end)
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		for (i = 0; trab[i]; i++)
		{
			if (*splitted == trab[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (str_start);
}

/**
 * _isdigit - defines if string passed is a number
 *
 * @string: input string
 * Return: 1 if string is a number. 0 in other case.
 */
int _isdigit(const char *string)
{
	unsigned int i;

	for (i = 0; string[i]; i++)
	{
		if (string[i] < 48 || string[i] > 57)
			return (0);
	}
	return (1);
}
