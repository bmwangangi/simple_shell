#include "shell.h"

/**
 * _stringatoi - converts the string
 * @a: the string
 * Return: 0
 */
int _stringatoi(char *a)
{
	int b = 0;
	unsigned long int rlt = 0;

	if (*a == '+')
		a++;
	for (b = 0;  a[b] != '\0'; b++)
	{
		if (a[b] >= '0' && a[b] <= '9')
		{
			rlt *= 10;
			rlt += (a[b] - '0');
			if (rlt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (rlt);
}

/**
 * printing_error - printing the error
 * @trab: the parameter
 * @string: string with the error
 * Return: 0
 */
void printing_error(info_t *trab, char *string)
{
	_eputs(trab->fname);
	_eputs(": ");
	print_d(trab->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(trab->argv[0]);
	_eputs(": ");
	_eputs(string);
}

/**
 * print_decimal - function prints a decimal number (base 10)
 * user: the input
 * @filed: the filedescriptor
 *
 * Return: printed characters
 */
int print_decimal(int user, int filed)
{
	int (*__putchar)(char) = _putchar;
	int a, counts = 0;
	unsigned int _as_, now;

	if (filed == STDERR_FILENO)
		__putchar = _eputchar;
	if (user < 0)
	{
		_as_ = -user;
		__putchar('-');
		counts++;
	}
	else
		_as_ = user;
	now = _as_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_as_ / a)
		{
			__putchar('0' + now / a);
			counts++;
		}
		now %= a;
	}
	__putchar('0' + now);
	counts++;

	return (counts);
}

/**
 * converting_no - converter function.
 * @number: number
 * @bs: base
 * @flag: arg flags
 *
 * Return: the string
 */
char *converting_no(long int number, int bs, int flag)
{
	static char *array;
	static char buffer[50];
	char status = 0;
	char *ptr;
	unsigned long a = number;

	if (!(flag & CONVERT_UNSIGNED) && number < 0)
	{
		a = -number;
		status = '-';

	}
	array = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[a % bs];
		a /= bs;
	} while (a != 0);

	if (status)
		*--ptr = status;
	return (ptr);
}

/**
 * removing_comments - replaces first instance of '#' with '\0'
 * @buffer: address of the string i need to modify
 *
 * Return: Always 0;
 */
void removing_comments(char *buffer)
{
	int a;

	for (a = 0; buffer[a] != '\0'; a++)
		if (buffer[a] == '#' && (!a || buffer[a - 1] == ' '))
		{
			buffer[a] = '\0';
			break;
		}
}
