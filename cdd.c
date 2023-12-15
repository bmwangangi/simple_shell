#include "main.h"

/**
 * cd_dot - New parent directory
 * @datashel: env data relevant
 * Return: return 0
 */
void cd_dot(d_shell *datashel)
{
	char pwdir[PATH_MAX];
	char *directory, *cp_pwdir, *cp_strtok_pwdir;

	getcwd(pwdir, sizeof(pwdir));
	cp_pwdir = _strdup(pwdir);
	set_env("OLDPWD", cp_pwdir, datashel);
	directory = datashel->args[1];
	if (_strcmp(".", directory) == 0)
	{
		set_env("PWD", cp_pwdir, datashel);
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
		set_env("PWD", cp_strtok_pwdir, datashel);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datashel);
	}
	datashel->status = 0;
	free(cp_pwdir);
}

/**
 * cd_to - dir changes
 *
 * @datashel: dir relevant data
 * Return: return 0
 */
void cd_to(d_shell *datashel)
{
	char pwdir[PATH_MAX];
	char *directory, *cp_pwdir, *cp_directory;

	getcwd(pwdir, sizeof(pwdir));

	directory = datashel->args[1];
	if (chdir(directory) == -1)
	{
		get_error(datashel, 2);
		return;
	}

	cp_pwdir = _strdup(pwdir);
	set_env("OLDPWD", cp_pwdir, datashel);

	cp_directory = _strdup(directory);
	set_env("PWD", cp_directory, datashel);

	free(cp_pwdir);
	free(cp_directory);

	datashel->status = 0;

	chdir(directory);
}

/**
 * cd_previous - prev dir changes
 * @datashel: env relevant data
 * Return: return 0
 */
void cd_previous(d_shell *datashel)
{
	char pwdir[PATH_MAX];
	char *p_pwdir, *p_oldpwdir, *cp_pwdir, *cp_oldpwdir;

	getcwd(pwdir, sizeof(pwdir));
	cp_pwdir = _strdup(pwdir);

	p_oldpwdir = _getenv("OLDPWD", datashel->_environ);

	if (p_oldpwdir == NULL)
		cp_oldpwdir = cp_pwdir;
	else
		cp_oldpwdir = _strdup(p_oldpwdir);

	set_env("OLDPWD", cp_pwdir, datashel);

	if (chdir(cp_oldpwdir) == -1)
		set_env("PWD", cp_pwdir, datashel);
	else
		set_env("PWD", cp_oldpwdir, datashel);

	p_pwdir = _getenv("PWD", datashel->_environ);

	write(STDOUT_FILENO, p_pwdir, _strlen(p_pwdir));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwdir);
	if (p_oldpwdir)
		free(cp_oldpwdir);

	datashel->status = 0;

	chdir(p_pwdir);
}

/**
 * cd_to_home - new home directory
 *
 * @datashel: env relevant data
 * Return: return 0
 */
void cd_to_home(d_shell *datashel)
{
	char *p_pwdir, *home;
	char pwdir[PATH_MAX];

	getcwd(pwdir, sizeof(pwdir));
	p_pwdir = _strdup(pwdir);

	home = _getenv("HOME", datashel->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwdir, datashel);
		free(p_pwdir);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(datashel, 2);
		free(p_pwdir);
		return;
	}

	set_env("OLDPWD", p_pwdir, datashel);
	set_env("PWD", home, datashel);
	free(p_pwdir);
	datashel->status = 0;
}
