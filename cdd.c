#include "main.h"

/**
 * cd_dot - New parent directory
 *
 * @datash: env data relevant
 *
 * Return: return 0
 */
void cd_dot(data_shell *datash)
{
	char pwdir[PATH_MAX];
	char *directory, *cp_pwdir, *cp_strtok_pwdir;

	getcwd(pwdir, sizeof(pwdir));
	cp_pwdir = _strdup(pwdir);
	set_env("OLDPWD", cp_pwdir, datash);
	directory = datash->args[1];
	if (_strcmp(".", directory) == 0)
	{
		set_env("PWD", cp_pwdir, datash);
		free(cp_pwdir);
		return;
	}
	if (_strcmp("/", cp_pwdir) == 0)
	{
		free(cp_pwdir);
		return;
	}
	cp_strtok_pwdir = cp_pwdir;
	rev_string(cp_strtok_pwdir);
	cp_strtok_pwdir = _strtok(cp_strtok_pwdir, "/");
	if (cp_strtok_pwdir != NULL)
	{
		cp_strtok_pwdir = _strtok(NULL, "\0");

		if (cp_strtok_pwdir != NULL)
			rev_string(cp_strtok_pwdir);
	}
	if (cp_strtok_pwdir != NULL)
	{
		chdir(cp_strtok_pwdir);
		set_env("PWD", cp_strtok_pwdir, datash);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datash);
	}
	datash->status = 0;
	free(cp_pwdir);
}

/**
 * cd_to - dir changes
 *
 * @datash: dir relevant data
 * Return: return 0
 */
void cd_to(data_shell *datash)
{
	char pwdir[PATH_MAX];
	char *directory, *cp_pwdir, *cp_directory;

	getcwd(pwdir, sizeof(pwdir));

	directory = datash->args[1];
	if (chdir(directory) == -1)
	{
		get_error(datash, 2);
		return;
	}

	cp_pwdir = _strdup(pwdir);
	set_env("OLDPWD", cp_pwdir, datash);

	cp_directory = _strdup(directory);
	set_env("PWD", cp_directory, datash);

	free(cp_pwdir);
	free(cp_directory);

	datash->status = 0;

	chdir(directory);
}

/**
 * cd_previous - prev dir changes
 *
 * @datash: env relevant data
 * Return: return 0
 */
void cd_previous(data_shell *datash)
{
	char pwdir[PATH_MAX];
	char *p_pwdir, *p_oldpwdir, *cp_pwdir, *cp_oldpwdir;

	getcwd(pwdir, sizeof(pwdir));
	cp_pwdir = _strdup(pwdir);

	p_oldpwdir = _getenv("OLDPWD", datash->_environ);

	if (p_oldpwdir == NULL)
		cp_oldpwdir = cp_pwdir;
	else
		cp_oldpwdir = _strdup(p_oldpwdir);

	set_env("OLDPWD", cp_pwdir, datash);

	if (chdir(cp_oldpwdir) == -1)
		set_env("PWD", cp_pwdir, datash);
	else
		set_env("PWD", cp_oldpwdir, datash);

	p_pwdir = _getenv("PWD", datash->_environ);

	write(STDOUT_FILENO, p_pwdir, _strlen(p_pwdir));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwdir);
	if (p_oldpwdir)
		free(cp_oldpwdir);

	datash->status = 0;

	chdir(p_pwdir);
}

/**
 * cd_to_home - new home directory
 *
 * @datash: env relevant data
 * Return: return 0
 */
void cd_to_home(data_shell *datash)
{
	char *p_pwdir, *home;
	char pwdir[PATH_MAX];

	getcwd(pwdir, sizeof(pwdir));
	p_pwdir = _strdup(pwdir);

	home = _getenv("HOME", datash->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwdir, datash);
		free(p_pwdir);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(datash, 2);
		free(p_pwdir);
		return;
	}

	set_env("OLDPWD", p_pwdir, datash);
	set_env("PWD", home, datash);
	free(p_pwdir);
	datash->status = 0;
}
