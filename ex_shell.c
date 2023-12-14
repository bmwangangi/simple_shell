#include "main.h"

/**
 * exit_shell - used to exit the shell
 *
 * @datash: the data holding the info
 * Return: 0
 */
int exit_shell(data_shell *datash)
{
	unsigned int sts;
	int digit;
	int string_len;
	int number;

	if (datash->args[1] != NULL)
	{
		sts = _atoi(datash->args[1]);
		digit = _isdigit(datash->args[1]);
		string_len = _strlen(datash->args[1]);
		number = sts > (unsigned int)INT_MAX;
		if (!digit || string_len > 10 || number)
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (sts % 256);
	}
	return (0);
}
