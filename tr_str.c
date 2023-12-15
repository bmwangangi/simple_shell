#include "main.h"

/**
 * _strcat - str concat
 * @destination: points copied str
 * @source: points source of str
 * Return: dest
 */
char *_strcat(char *destination, const char *source)
{
	int k;
	int l;

	for (k = 0; destination[k] != '\0'; k++)
		;

	for (l = 0; source[l] != '\0'; l++)
	{
		destination[k] = source[k];
		k++;
	}

	destination[k] = '\0';
	return (destination);
}
/**
 * *_strcpy - Copies str
 * @destination: points copied str
 * @source: points source of str
 * Return: dest.
 */
char *_strcpy(char *destination, char *source)
{

	size_t r;

	for (r = 0; source[r] != '\0'; r++)
	{
		destination[r] = source[r];
	}
	destination[r] = '\0';

	return (destination);
}
/**
 * _strcmp - Function that compares two strings.
 * @str1: type str compared
 * @str2: type str compared
 * Return: Always 0.
 */
int _strcmp(char *str1, char *str2)
{
	int k;

	for (k = 0; str1[k] == str2[k] && str1[k]; k++)
		;

	if (str1[k] > str2[k])
		return (1);
	if (str1[k] < str2[k])
		return (-1);
	return (0);
}
/**
 * _strchr - char location
 * @character: char
 * @string: str
 * Return: pointer is 1st occurrence
 */
char *_strchr(char *string, char character)
{
	unsigned int k = 0;

	for (; *(string + k) != '\0'; k++)
		if (*(string + k) == character)
			return (string + k);
	if (*(string + k) == character)
		return (string + k);
	return ('\0');
}
/**
 * _strspn - len of substring
 * @string: prev subline
 * @accepting: bytes acc
 * Return: count of acc bytes
 */
int _strspn(char *string, char *accepting)
{
	int k, l, bool;

	for (k = 0; *(string + k) != '\0'; k++)
	{
		bool = 1;
		for (l = 0; *(accepting + l) != '\0'; l++)
		{
			if (*(string + k) == *(accepting + l))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (k);
}
