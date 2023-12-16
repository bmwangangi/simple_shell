
#include "main.h"

/**
 * strcat_cd -  Concatenates an error message for the 'cd' command.
 *
 * @datash:Shell data containing relevant information.
 * @msg: Output buffer for the error message.
 * @error:Counter lines as a string.
 * @ver_str: the number of lines
 * Return: error message
 */
char *strcat_cd(data_shell *datash, char *msg, char *error, char *ver_str)
{
	char *illegal_option;

	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, msg);
	if (datash->args[1][0] == '-')
	{
		illegal_option = malloc(3);
		illegal_option[0] = '-';
		illegal_option[1] = datash->args[1][1];
		illegal_option[2] = '\0';
		_strcat(error, illegal_option);
		free(illegal_option);
	}
	else
	{
		_strcat(error, datash->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_cd - Generates an error message for the 'cd' command in the get_cd function.
 * @datash: hell data containing relevant information.
 * Return: Error message
 */
char *error_get_cd(data_shell *datash)
{
	int totallength, idlength;
	char *errormessage, *counter_str, *message;

	counter_str = aux_itoa(datash->counter);
	if (datash->args[1][0] ==  '-')
	{
		message = ": Illegal option ";
		idlength = 2;
	}
	else
	{
		message = ": can't cd to ";
		idlength = _strlen(datash->args[1]);
	}

	totallength = _strlen(datash->av[0]) + _strlen(datash->args[0]);
	totallength += _strlen(counter_str) + _strlen(message) + idlength + 5;
	errormessage = malloc(sizeof(char) * (totallength + 1));

	if (errormessage == 0)
	{
		free(counter_str);
		return (NULL);
	}

	errormessage = strcat_cd(datash, message, errormessage, counter_str);

	free(counter_str);

	return (errormessage);
}

/**
 * error_not_found - Generates a generic error message for command not found.
 * @datash: Shell data containing relevant information.
 * Return: Error message
 */
char *error_not_found(data_shell *datash)
{
	int totallength;
	char *errormessage;
	char *counter_str;

	counter_str = aux_itoa(datash->counter);
	totallength = _strlen(datash->av[0]) + _strlen(counter_str);
	totallength += _strlen(datash->args[0]) + 16;
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
	_strcat(errormessage, ": not found\n");
	_strcat(errormessage, "\0");
	free(counter_str);
	return (errormessage);
}

/**
 * error_exit_shell - Generates a generic error message for 'exit' in the get_exit function.
 * @datash: Shell data containing relevant information.
 *
 * Return: Error message
 */
char *error_exit_shell(data_shell *datash)
{
	int totallength;
	char *errormessage;
	char *counter_str;

	counter_str = aux_itoa(datash->counter);
	totallength = _strlen(datash->av[0]) + _strlen(counter_str);
	totallength += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;
	errormessage = malloc(sizeof(char) * (totallength + 1));
	if (errormessage == 0)
	{
		free(counter_str);
		return (NULL);
	}
	_strcpy(errormessage, datash->av[0]);
	_strcat(errormessage, ": ");
	_strcat(errormessage, counter_str);
	_strcat(errormessage, ": ");
	_strcat(errormessage, datash->args[0]);
	_strcat(errormessage, ": Illegal no: ");
	_strcat(errormessage, datash->args[1]);
	_strcat(errormessage, "\n\0");
	free(counter_str);

	return (errormessage);
}
