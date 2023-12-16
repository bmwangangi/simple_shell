#include "main.h"

/**
 * error_env - Err sent for env in get_env.
 * @datash: relevant data for counters
 * Return: An error
 */
char *error_env(data_shell *datash)
{
	int totallength;
	char *errormessage;
	char *counter_str;
	char *message;

	counter_str = aux_itoa(datash->counter);
	message = ": Error when trying to add/remove from env\n";
	totallength = _strlen(datash->av[0]) + _strlen(counter_str);
	totallength += _strlen(datash->args[0]) + _strlen(message) + 4;
	errormessage= malloc(sizeof(char) * (totallength + 1));
	if (errormessage == 0)
	{
		free(errormessage);
		free(counter_str);
		return (NULL);
	}

	_strcpy(errormessage, datash->av[0]);
	_strcat(errormessage, ": ");
	_strcat(errormessage, counter_str);
	_strcat(errormessage, ": ");
	_strcat(errormessage, datash->args[0]);
	_strcat(errormessage, message);
	_strcat(errormessage, "\0");
	free(counter_str);

	return (errormessage);
}
/**
 * error_path_126 - Denied permission
 * @datash: Relevant data, counter
 *
 * Return: The error string.
 */
char *error_path_126(data_shell *datash)
{
	int totallength;
	char *counter_str;
	char *errormessage;

	counter_str = aux_itoa(datash->counter);
	totallength = _strlen(datash->av[0]) + _strlen(counter_str);
	totallength += _strlen(datash->args[0]) + 24;
	errormessage = malloc(sizeof(char) * (totallength + 1));
	if (errormessage == 0)
	{
		free(errormessage);
		free(counter_str);
		return (NULL);
	}
	_strcpy(errormessage, datash->av[0]);
	_strcat(errormessage, ": ");
	_strcat(errormessage, counter_str);
	_strcat(errormessage, ": ");
	_strcat(errormessage, datash->args[0]);
	_strcat(errormessage, ": Hit a wall\n");
	_strcat(errormessage, "\0");
	free(counter_str);
	return (errormessage);

}
