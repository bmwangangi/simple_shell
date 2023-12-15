#include "main.h"

/**
 * without_comment - removes all the comments from the input
 * @inp: the string to input
 * Return: no comments
 */
char *without_comment(char *inp)
{
	int a, where;

	where = 0;
	for (a = 0; inp[a]; a++)
	{
		if (inp[a] == '#')
		{
			if (a == 0)
			{
				free(inp);
				return (NULL);
			}

			if (inp[a - 1] == ' ' || inp[a - 1] == '\t' || inp[a - 1] == ';')
				where = a;
		}
	}

	if (where != 0)
	{
		inp = _realloc(inp, a, where + 1);
		inp[where] = '\0';
	}

	return (inp);
}

/**
 * shell_loop - the looping of the shell
 * @datashel: the data holding the infomation
 * Return: 0
 */
void shell_loop(d_shell *datashel)
{
	int looping, where;
	char *insert;

	looping = 1;
	while (looping == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		insert = read_line(&where);
		if (where != -1)
		{
			insert = without_comment(insert);
			if (insert == NULL)
				continue;

			if (check_syntax_error(datashel, insert) == 1)
			{
				datashel->status = 2;
				free(insert);
				continue;
			}
			insert = rep_var(insert, datashel);
			looping = split_commands(datashel, insert);
			datashel->counter += 1;
			free(insert);
		}
		else
		{
			looping = 0;
			free(insert);
		}
	}
}
