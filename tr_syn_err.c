#include "main.h"

/**
 * repeated_char - counts rep char
 * @input: inp str
 * @i: index
 * Return: rep
 */
int repeated_char(char *input, int r)
{
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, r + 1));

	return (r);
}

/**
 * error_sep_op - Syntax x
 * @input: str inp
 * @i: index
 * @last: last character
 * Return: 0 when no error /index of error when there is error
 */
int error_sep_op(char *input, int r, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_sep_op(input + 1, r + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (r);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (r);

		if (last == '|')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (r);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (r);

		if (last == '&')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (r);
		}
	}

	return (error_sep_op(input + 1, r + 1, *input));
}

/**
 * first_char - 1st char index
 * @input: str inp
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */
int first_char(char *input, int *r)
{

	for (*r = 0; input[*r]; *r += 1)
	{
		if (input[*r] == ' ' || input[*r] == '\t')
			continue;

		if (input[*r] == ';' || input[*r] == '|' || input[*r] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error - when there is syntax error, it prints
 * @datash: structure: 
 * @input: str inp
 * @i: error index
 * @bool: there to control msg error
 * Return: 0 or no
 */
void print_syntax_error(data_shell *datash, char *input, int r, int bool)
{
	char *msg, *messg2, *messg3, *error, *counter;
	int length;

	if (input[r] == ';')
	{
		if (bool == 0)
			msg = (input[r + 1] == ';' ? ";;" : ";");
		else
			msg = (input[r - 1] == ';' ? ";;" : ";");
	}

	if (input[r] == '|')
		msg = (input[r + 1] == '|' ? "||" : "|");

	if (input[r] == '&')
		msg = (input[r + 1] == '&' ? "&&" : "&");

	messg2 = ": Syntax error: \"";
	messg3 = "\" unexpected\n";
	counter = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(messg2) + _strlen(messg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, messg2);
	_strcat(error, msg);
	_strcat(error, messg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * check_syntax_error - find and print syntax error
 * @datash: struc:
 * @input: str inp
 * Return: 1 if there is an error. 0 in other case
 */
int check_syntax_error(data_shell *datash, char *input)
{
	int b = 0;
	int f_char = 0;
	int r = 0;

	f_char = first_char(input, &b);
	if (f_char == -1)
	{
		print_syntax_error(datash, input, b, 0);
		return (1);
	}

	r = error_sep_op(input + b, 0, *(input + b));
	if (r != 0)
	{
		print_syntax_error(datash, input, b + r, 1);
		return (1);
	}

	return (0);
}
