#include "main.h"

/**
 * _strcat - str concat
 * @dest: points copied str
 * @src: points source of str
 * Return: dest
 */
char *_strcat(char *dest, const char *src)
{
	int k;
	int l;

	for (k = 0; dest[k] != '\0'; k++)
		;

	for (l = 0; src[l] != '\0'; l++)
	{
		dest[k] = src[k];
		k++;
	}

	dest[k] = '\0';
	return (dest);
}
/**
 * *_strcpy - Copies str
 * @dest: points copied str
 * @src: points source of str
 * Return: dest.
 */
char *_strcpy(char *dest, char *src)
{

	size_t r;

	for (r = 0; src[r] != '\0'; r++)
	{
		dest[r] = src[r];
	}
	dest[r] = '\0';

	return (dest);
}
/**
 * _strcmp - Function that compares two strings.
 * @s1: type str compared
 * @s2: type str compared
 * Return: Always 0.
 */
int _strcmp(char *s1, char *s2)
{
	int k;

	for (k = 0; s1[k] == s2[k] && s1[k]; k++)
		;

	if (s1[k] > s2[k])
		return (1);
	if (s1[k] < s2[k])
		return (-1);
	return (0);
}
/**
 * _strchr - char location
 * @c: char
 * @s: str
 * Return: pointer is 1st occurrence
 */
char *_strchr(char *s, char c)
{
	unsigned int k = 0;

	for (; *(s + k) != '\0'; k++)
		if (*(s + k) == c)
			return (s + k);
	if (*(s + k) == c)
		return (s + k);
	return ('\0');
}
/**
 * _strspn - len of substring
 * @s: prev subline
 * @accept: bytes acc
 * Return: count of acc bytes
 */
int _strspn(char *s, char *accept)
{
	int k, l, bool;

	for (k = 0; *(s + k) != '\0'; k++)
	{
		bool = 1;
		for (l = 0; *(accept + l) != '\0'; l++)
		{
			if (*(s + k) == *(accept + l))
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
