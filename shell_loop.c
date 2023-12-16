#include "main.h"

/**
 * without_comment - removes all the comments from the input
 *
 * @in: the string to input
 * Return: no comments
 */
char *without_comment(char *in)
{
	int a, where;

	where = 0;
	for (a = 0; in[a]; a++)
	{
		if (in[a] == '#')
		{
			if (a == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[a - 1] == ' ' || in[a - 1] == '\t' || in[a - 1] == ';')
				where = a;
		}
	}

	if (where != 0)
	{
		in = _realloc(in, a, where + 1);
		in[where] = '\0';
	}

	return (in);
}

/**
 * shell_loop - the looping of the shell
 * @datash: the data holding the infomation
 *
 * Return: 0
 */
void shell_loop(data_shell *datash)
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

			if (check_syntax_error(datash, insert) == 1)
			{
				datash->status = 2;
				free(insert);
				continue;
			}
			insert = rep_var(insert, datash);
			looping = split_commands(datash, insert);
			datash->counter += 1;
			free(insert);
		}
		else
		{
			looping = 0;
			free(insert);
		}
	}
}
