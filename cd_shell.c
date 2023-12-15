#include "main.h"

/**
 * cd_shell - used for changing directories
 * @datashel: the data available
 * Return: 1
 */
int cd_shell(d_shell *datashel)
{
	char *directory;
	int homevariable, homevariable2, doubledash;

	directory = datashel->args[1];

	if (directory != NULL)
	{
		homevariable = _strcmp("$HOME", directory);
		homevariable2 = _strcmp("~", directory);
		doubledash = _strcmp("--", directory);
	}

	if (directory == NULL || !homevariable || !homevariable2 || !doubledash)
	{
		cd_to_home(datashel);
		return (1);
	}

	if (_strcmp("-", directory) == 0)
	{
		cd_previous(datashel);
		return (1);
	}

	if (_strcmp(".", directory) == 0 || _strcmp("..", directory) == 0)
	{
		cd_dot(datashel);
		return (1);
	}

	cd_to(datashel);

	return (1);
}
