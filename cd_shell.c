#include "main.h"

/**
 * cd_shell - used for changing directories
 *
 * @datash: the data available
 * Return: 1
 */
int cd_shell(data_shell *datash)
{
	char *directory;
	int homevariable, homevariable2, doubledash;

	directory = datash->args[1];

	if (directory != NULL)
	{
		homevariable = _strcmp("$HOME", directory);
		homevariable2 = _strcmp("~", directory);
		doubledash = _strcmp("--", directory);
	}

	if (directory == NULL || !homevariable || !homevariable2 || !doubledash)
	{
		cd_to_home(datash);
		return (1);
	}

	if (_strcmp("-", directory) == 0)
	{
		cd_previous(datash);
		return (1);
	}

	if (_strcmp(".", directory) == 0 || _strcmp("..", directory) == 0)
	{
		cd_dot(datash);
		return (1);
	}

	cd_to(datash);

	return (1);
}
