
#include "main.h"

/**
 * strcat_cd - Concatenates an error message for the 'cd' command.
 * @datashel: Shell data containing relevant information.
 * @message: Output buffer for the error message.
 * @err: Counter lines as a string.
 * @ver_string: the number of lines
 * Return: error message
 */
char *strcat_cd(d_shell *datashel, char *message, char *err, char *ver_string)
{
	char *illegal_option;

	_strcpy(err, datashel->av[0]);
	_strcat(err, ": ");
	_strcat(err, ver_string);
	_strcat(err, ": ");
	_strcat(err, datashel->args[0]);
	_strcat(err, message);
	if (datashel->args[1][0] == '-')
	{
		illegal_option = malloc(3);
		illegal_option[0] = '-';
		illegal_option[1] = datashel->args[1][1];
		illegal_option[2] = '\0';
		_strcat(err, illegal_option);
		free(illegal_option);
	}
	else
	{
		_strcat(err, datashel->args[1]);
	}

	_strcat(err, "\n");
	_strcat(err, "\0");
	return (err);
}

/**
 * error_get_cd - Generates an error message for the 'cd' command in the get_cd function.
 * @datashel: hell data containing relevant information.
 * Return: Error message
 */
char *error_get_cd(d_shell *datashel)
{
	int totallength, idlength;
	char *errormessage, *counter_str, *message;

	counter_str = aux_itoa(datashel->counter);
	if (datashel->args[1][0] ==  '-')
	{
		message = ": Illegal option ";
		idlength = 2;
	}
	else
	{
		message = ": can't cd to ";
		idlength = _strlen(datashel->args[1]);
	}

	totallength = _strlen(datashel->av[0]) + _strlen(datashel->args[0]);
	totallength += _strlen(counter_str) + _strlen(message) + idlength + 5;
	errormessage = malloc(sizeof(char) * (totallength + 1));

	if (errormessage == 0)
	{
		free(counter_str);
		return (NULL);
	}

	errormessage = strcat_cd(datashel, message, errormessage, counter_str);

	free(counter_str);

	return (errormessage);
}

/**
 * error_not_found - Generates a generic error message for command not found.
 * @datashel: Shell data containing relevant information.
 * Return: Error message
 */
char *error_not_found(d_shell *datashel)
{
	int totallength;
	char *errormessage;
	char *counter_str;

	counter_str = aux_itoa(datashel->counter);
	totallength = _strlen(datashel->av[0]) + _strlen(counter_str);
	totallength += _strlen(datashel->args[0]) + 16;
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
	_strcat(errormessage, ": not found\n");
	_strcat(errormessage, "\0");
	free(counter_str);
	return (errormessage);
}

/**
 * error_exit_shell - Generates a generic error message for 'exit' in the get_exit function.
 * @datashel: Shell data containing relevant information.
 * Return: Error message
 */
char *error_exit_shell(d_shell *datashel)
{
	int totallength;
	char *errormessage;
	char *counter_str;

	counter_str = aux_itoa(datashel->counter);
	totallength = _strlen(datashel->av[0]) + _strlen(counter_str);
	totallength += _strlen(datashel->args[0]) + _strlen(datashel->args[1]) + 23;
	errormessage = malloc(sizeof(char) * (totallength + 1));
	if (errormessage == 0)
	{
		free(counter_str);
		return (NULL);
	}
	_strcpy(errormessage, datashel->av[0]);
	_strcat(errormessage, ": ");
	_strcat(errormessage, counter_str);
	_strcat(errormessage, ": ");
	_strcat(errormessage, datashel->args[0]);
	_strcat(errormessage, ": Illegal no: ");
	_strcat(errormessage, datashel->args[1]);
	_strcat(errormessage, "\n\0");
	free(counter_str);

	return (errormessage);
}
