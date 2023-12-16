#include "main.h"

/**
 * cmp_env_name - used for comparison for enviroment variables
 * @nenv: name of the variable
 * @name: the one passed
 *
 * Return: 0
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int a;

	for (a = 0; nenv[a] != '='; a++)
	{
		if (nenv[a] != name[a])
		{
			return (0);
		}
	}

	return (a + 1);
}

/**
 * _getenv - usedto get the enviroment variable
 * @name: name of the variable
 * @_environ: env variable
 *
 * Return: value of the env variable
 */
char *_getenv(const char *name, char **_environ)
{
	char *print_env;
	int a, move;

	print_env = NULL;
	move = 0;

	for (a = 0; _environ[a]; a++)
	{
		move = cmp_env_name(_environ[a], name);
		if (move)
		{
			print_env = _environ[a];
			break;
		}
	}

	return (print_env + move);
}

/**
 * _env - used to print the variable for the enviroment
 *
 * @datash: the data with information
 * Return: 1
 */
int _env(data_shell *datash)
{
	int a, b;

	for (a = 0; datash->_environ[a]; a++)
	{

		for (b = 0; datash->_environ[a][b]; b++);

		write(STDOUT_FILENO, datash->_environ[a], b);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
