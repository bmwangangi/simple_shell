
#include "main.h"

/**
 * rev_string - str reverse
 * @string: str inp
 * Return: always 0
 */
void rev_string(char *string)
{
	int count = 0, k, l;
	char *str, temp;

	while (count >= 0)
	{
		if (string[count] == '\0')
			break;
		count++;
	}
	str = string;

	for (k = 0; k < (count - 1); k++)
	{
		for (l = k + 1; l > 0; l--)
		{
			temp = *(str + l);
			*(str + l) = *(str + (l - 1));
			*(str + (l - 1)) = temp;
		}
	}
}
