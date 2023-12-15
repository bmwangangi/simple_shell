#include "main.h"

/**
 * repeated_char - counts rep char
 * @inp: inp str
 * @r: index
 * Return: rep
 */
int repeated_char(char *inp, int r)
{
	if (*(inp - 1) == *inp)
		return (repeated_char(inp - 1, r + 1));

	return (r);
}

/**
 * error_sep_op - Syntax x
 * @inp: str inp
 * @r: index
 * @lst: last character
 * Return: 0 when no error /index of error when there is error
 */
int error_sep_op(char *inp, int r, char lst)
{
	int count;

	count = 0;
	if (*inp == '\0')
		return (0);

	if (*inp == ' ' || *inp == '\t')
		return (error_sep_op(inp + 1, r + 1, lst));

	if (*inp == ';')
		if (lst == '|' || lst == '&' || lst == ';')
			return (r);

	if (*inp == '|')
	{
		if (lst == ';' || lst == '&')
			return (r);

		if (lst == '|')
		{
			count = repeated_char(inp, 0);
			if (count == 0 || count > 1)
				return (r);
		}
	}

	if (*inp == '&')
	{
		if (lst == ';' || lst == '|')
			return (r);

		if (lst == '&')
		{
			count = repeated_char(inp, 0);
			if (count == 0 || count > 1)
				return (r);
		}
	}

	return (error_sep_op(inp + 1, r + 1, *inp));
}

/**
 * first_char - 1st char index
 * @inp: str inp
 * @r: index
 * Return: 1 if there is an error. 0 in other case.
 */
int first_char(char *inp, int *r)
{

	for (*r = 0; inp[*r]; *r += 1)
	{
		if (inp[*r] == ' ' || inp[*r] == '\t')
			continue;

		if (inp[*r] == ';' || inp[*r] == '|' || inp[*r] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error - when there is syntax error, it prints
 * @datashel: structure:
 * @inp: str inp
 * @r: error index
 * @bool: there to control msg error
 * Return: 0 or no
 */
void print_syntax_error(d_shell *datashel, char *inp, int r, int bool)
{
	char *msg, *messg2, *messg3, *error, *counter;
	int length;

	if (inp[r] == ';')
	{
		if (bool == 0)
			msg = (inp[r + 1] == ';' ? ";;" : ";");
		else
			msg = (inp[r - 1] == ';' ? ";;" : ";");
	}

	if (inp[r] == '|')
		msg = (inp[r + 1] == '|' ? "||" : "|");

	if (inp[r] == '&')
		msg = (inp[r + 1] == '&' ? "&&" : "&");

	messg2 = ": Syntax error: \"";
	messg3 = "\" unexpected\n";
	counter = aux_itoa(datashel->counter);
	length = _strlen(datashel->av[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(messg2) + _strlen(messg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, datashel->av[0]);
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
 * @datashel: struc:
 * @inp: str inp
 * Return: 1 if there is an error. 0 in other case
 */
int check_syntax_error(d_shell *datashel, char *inp)
{
	int b = 0;
	int f_char = 0;
	int r = 0;

	f_char = first_char(inp, &b);
	if (f_char == -1)
	{
		print_syntax_error(datashel, inp, b, 0);
		return (1);
	}

	r = error_sep_op(inp + b, 0, *(inp + b));
	if (r != 0)
	{
		print_syntax_error(datashel, inp, b + r, 1);
		return (1);
	}

	return (0);
}
