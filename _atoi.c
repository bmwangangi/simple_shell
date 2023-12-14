#include "shell.h"

/**
 * interactive - works in interactive mode
 * @trab: the address
 *
 * Return: 1 in interactive qnd 0 if not
 */
int interactive(info_t *trab)
{
	return (isatty(STDIN_FILENO) && trab->readfd <= 2);
}

/**
 * is_delim - checks the character
 * @t: the char we are watching
 * @delimiter: the  string
 * Return: 1 if true, 0 if false
 */
int is_delim(char t, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == t)
			return (1);
	return (0);
}

/**
 *_isalphabhet - checks for alphabets
 *@t: The character
 *Return: 1 if t is alphabetic, 0 otherwise
 */

int _isalphabhet(int t)
{
	if ((t >= 'a' && t <= 'z') || (t >= 'A' && t <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - used fot conversion of a string
 *@t: the string
 *Return: 0 if no numbers in string
 */

int _atoi(char *t)
{
	int i, sign = 1, flag = 0, output;
	unsigned int final = 0;

	for (i = 0;  t[i] != '\0' && flag != 2; i++)
	{
		if (t[i] == '-')
			sign *= -1;

		if (t[i] >= '0' && t[i] <= '9')
		{
			flag = 1;
			final *= 10;
			final += (t[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -final;
	else
		output = final;

	return (output);
}
