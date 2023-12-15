#include "main.h"

/**
 * exit_shell - used to exit the shell
 * @datashel: the data holding the info
 * Return: 0
 */
int exit_shell(d_shell *datashel)
{
	unsigned int sts;
	int digit;
	int string_len;
	int number;

	if (datashel->args[1] != NULL)
	{
		sts = _atoi(datashel->args[1]);
		digit = _isdigit(datashel->args[1]);
		string_len = _strlen(datashel->args[1]);
		number = sts > (unsigned int)INT_MAX;
		if (!digit || string_len > 10 || number)
		{
			get_error(datashel, 2);
			datashel->status = 2;
			return (1);
		}
		datashel->status = (sts % 256);
	}
	return (0);
}
