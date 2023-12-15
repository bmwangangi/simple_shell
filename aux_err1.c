#include "main.h"

/**
 * error_env - Err sent for env in get_env.
 * @datashel: relevant data for counters
 * Return: An error
 */
char *error_env(d_shell *datashel)
{
	int totallength;
	char *errormessage;
	char *counter_str;
	char *message;

	counter_str = aux_itoa(datashel->counter);
	message = ": Error when trying to add/remove from env\n";
	totallength = _strlen(datashel->av[0]) + _strlen(counter_str);
	totallength += _strlen(datashel->args[0]) + _strlen(message) + 4;
	errormessage= malloc(sizeof(char) * (totallength + 1));
	if (errormessage == 0)
	{
		free(errormessage);
		free(counter_str);
		return (NULL);
	}

	_strcpy(errormessage, datashel->av[0]);
	_strcat(errormessage, ": ");
	_strcat(errormessage, counter_str);
	_strcat(errormessage, ": ");
	_strcat(errormessage, datashel->args[0]);
	_strcat(errormessage, message);
	_strcat(errormessage, "\0");
	free(counter_str);

	return (errormessage);
}
/**
 * error_path_126 - Denied permission
 * @datashel: Relevant data, counter
 *
 * Return: The error string.
 */
char *error_path_126(d_shell *datashel)
{
	int totallength;
	char *counter_str;
	char *errormessage;

	counter_str = aux_itoa(datashel->counter);
	totallength = _strlen(datashel->av[0]) + _strlen(counter_str);
	totallength += _strlen(datashel->args[0]) + 24;
	errormessage = malloc(sizeof(char) * (totallength + 1));
	if (errormessage == 0)
	{
		free(errormessage);
		free(counter_str);
		return (NULL);
	}
	_strcpy(errormessage, datashel->av[0]);
	_strcat(errormessage, ": ");
	_strcat(errormessage, counter_str);
	_strcat(errormessage, ": ");
	_strcat(errormessage, datashel->args[0]);
	_strcat(errormessage, ": Hit a wall\n");
	_strcat(errormessage, "\0");
	free(counter_str);
	return (errormessage);

}
