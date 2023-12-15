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
 * @joe: name of the variable
 * @_environment: env variable
 * Return: value of the env variable
 */
char *_getenv(const char *joe, char **_environment)
{
	char *print_env;
	int a, move;

	print_env = NULL;
	move = 0;

	for (a = 0; _environment[a]; a++)
	{
		move = cmp_env_name(_environment[a], joe);
		if (move)
		{
			print_env = _environment[a];
			break;
		}
	}

	return (print_env + move);
}

/**
 * _env - used to print the variable for the enviroment
 * @datashel: the data with information
 * Return: 1
 */
int _env(d_shell *datashel)
{
	int a, b;

	for (a = 0; datashel->_environ[a]; a++)
	{

		for (b = 0; datashel->_environ[a][b]; b++);

		write(STDOUT_FILENO, datashel->_environ[a], b);
		write(STDOUT_FILENO, "\n", 1);
	}
	datashel->status = 0;

	return (1);
}
