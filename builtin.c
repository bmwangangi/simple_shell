#include "shell.h"

/**
 * _myexit - terminates the shell
 * @trab: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *trab)
{
	int exitzone;

	if (trab->argv[1])
	{
		exitzone = _atoi(trab->argv[1]);
		if (exitzone == -1)
		{
			trab->status = 2;
			printing_error(trab, "unrecognised  number: ");
			_inputs(trab->argv[1]);
			_putchar('\n');
			return (1);
		}
		trab->err_num = _atoi(trab->argv[1]);
		return (-2);
	}
	trab->err_num = -1;
	return (-2);
}

/**
 * _myowncd - changes the current directory
 * @trab: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myowncd(info_t *trab)
{
	char *t, *directory, buffer[1024];
	int chdir_zone;

	t = getcwd(buffer, 1024);
	if (!t)
		puts("TODO: >>getcwd failure emsg here<<\n");
	if (!trab->argv[1])
	{
		directory = getenv(trab, "HOME=");
		if (!directory)
			chdir_zone = /* TODO: what should this be? */
				chdir((directory = _getenv(trab, "PWD=")) ? directory : "/");
		else
			chdir_zone = chdir(directory);
	}
	else if (strcmp(trab->argv[1], "-") == 0)
	{
		if (!_getenv(trab, "OLDPWD="))
		{
			_puts(t);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(trab, "OLDPWD=")), _putchar('\n');
		chdir_zone = /* TODO: what should this be? */
			chdir((directory = _getenv(trab, "OLDPWD=")) ? directory : "/");
	}
	else
		chdir_zone = chdir(trab->argv[1]);
	if (chdir_zone == -1)
	{
		printing_error(trab, "can't cd to ");
		_eputs(trab->argv[1]), _eputchar('\n');
	}
	else
	{
		setenv(trab, "OLDPWD", _getenv(trab, "PWD="));
		_setenv(trab, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _help - changes the current directory
 * @trab: Structure containing arg
 *  Return: Always 0
 */
int _help(info_t *trab)
{
	char **argument_array;

	argument_array = trab->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argument_array); /* temp att_unused workaround */
	return (0);
}
