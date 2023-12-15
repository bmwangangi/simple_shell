#include "main.h"

/**
 * is_cdir - checks if ":" this is in the directory
 * @way: the pointer to data
 * @a: pointer of index
 * Return: 1
 */
int is_cdir(char *way, int *a)
{
	if (way[*a] == ':')
		return (1);

	while (way[*a] != ':' && way[*a])
	{
		*a += 1;
	}

	if (way[*a])
		*a += 1;

	return (0);
}

/**
 * _which - used for commannd location
 *
 * @cmd: the name of the command
 * @_environment: the variable representing enviroment
 * Return: the location of the command
 */
char *_which(char *cmd, char **_environment)
{
	char *fullpath, *pointer_path, *tkn_path, *directory;
	int length_dir, length_cmd, a;
	struct stat st;

	fullpath = _getenv("PATH", _environment);
	if (fullpath)
	{
		pointer_path = _strdup(fullpath);
		length_cmd = _strlen(cmd);
		tkn_path = _strtok(pointer_path, ":");
		a = 0;
		while (tkn_path != NULL)
		{
			if (is_cdir(fullpath, &a))
				if (stat(cmd, &st) == 0)
					return (cmd);
			length_dir = _strlen(tkn_path);
			directory = malloc(length_dir + length_cmd + 2);
			_strcpy(directory, tkn_path);
			_strcat(directory, "/");
			_strcat(directory, cmd);
			_strcat(directory, "\0");
			if (stat(directory, &st) == 0)
			{
				free(pointer_path);
				return (directory);
			}
			free(directory);
			tkn_path = _strtok(NULL, ":");
		}
		free(pointer_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executable - used to check if a file is executable
 *
 * @datashel: the data with the information
 * Return: 0
 */
int is_executable(d_shell *datashel)
{
	struct stat st;
	int a;
	char *insert;

	insert = datashel->args[0];
	for (a = 0; insert[a]; a++)
	{
		if (insert[a] == '.')
		{
			if (insert[a + 1] == '.')
				return (0);
			if (insert[a + 1] == '/')
				continue;
			else
				break;
		}
		else if (insert[a] == '/' && a != 0)
		{
			if (insert[a + 1] == '.')
				continue;
			a++;
			break;
		}
		else
			break;
	}
	if (a == 0)
		return (0);

	if (stat(insert + a, &st) == 0)
	{
		return (a);
	}
	get_error(datashel, 127);
	return (-1);
}

/**
 * check_error_cmd - verifies user access
 *
 * @directory: our destination dir
 * @datashel: the data containing the infomation
 * Return: 1
 */
int check_error_cmd(char *directory, d_shell *datashel)
{
	if (directory == NULL)
	{
		get_error(datashel, 127);
		return (1);
	}

	if (_strcmp(datashel->args[0], directory) != 0)
	{
		if (access(directory, X_OK) == -1)
		{
			get_error(datashel, 126);
			free(directory);
			return (1);
		}
		free(directory);
	}
	else
	{
		if (access(datashel->args[0], X_OK) == -1)
		{
			get_error(datashel, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_exec - used to execute
 *
 * @datashel: the data containing info
 * Return: 1
 */
int cmd_exec(d_shell *datashel)
{
	pid_t pd;
	pid_t wpd;
	int processstate;
	int executionflag;
	char *directory;
	(void) wpd;

	executionflag = is_executable(datashel);
	if (executionflag == -1)
		return (1);
	if (executionflag == 0)
	{
		directory = _which(datashel->args[0], datashel->_environ);
		if (check_error_cmd(directory, datashel) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (executionflag == 0)
			directory = _which(datashel->args[0], datashel->_environ);
		else
			directory = datashel->args[0];
		execve(directory + executionflag, datashel->args, datashel->_environ);
	}
	else if (pd < 0)
	{
		perror(datashel->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &processstate, WUNTRACED);
		} while (!WIFEXITED(processstate) && !WIFSIGNALED(processstate));
	}

	datashel->status = processstate / 256;
	return (1);
}
