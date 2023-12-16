#include "main.h"

/**
 * is_cdir - checks if ":" this is in the directory
 * @path: the pointer to data
 * @i: pointer of index
 * Return: 1
 */
int is_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _which - used for commannd location
 *
 * @cmd: the name of the command
 * @_environ: the variable representing enviroment
 * Return: the location of the command
 */
char *_which(char *cmd, char **_environ)
{
	char *fullpath, *pointer_path, *tkn_path, *directory;
	int length_dir, length_cmd, a;
	struct stat st;

	fullpath = _getenv("PATH", _environ);
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
 * @datash: the data with the information
 * Return: 0
 */
int is_executable(data_shell *datash)
{
	struct stat st;
	int a;
	char *insert;

	insert = datash->args[0];
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
	get_error(datash, 127);
	return (-1);
}

/**
 * check_error_cmd - verifies user access
 *
 * @dir: our destination dir
 * @datash: the data containing the infomation
 * Return: 1
 */
int check_error_cmd(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		get_error(datash, 127);
		return (1);
	}

	if (_strcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			get_error(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_exec - used to execute
 *
 * @datash: the data containing info
 * Return: 1
 */
int cmd_exec(data_shell *datash)
{
	pid_t pd;
	pid_t wpd;
	int processstate;
	int executionflag;
	char *directory;
	(void) wpd;

	executionflag = is_executable(datash);
	if (executionflag == -1)
		return (1);
	if (executionflag == 0)
	{
		directory = _which(datash->args[0], datash->_environ);
		if (check_error_cmd(directory, datash) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (executionflag == 0)
			directory = _which(datash->args[0], datash->_environ);
		else
			directory = datash->args[0];
		execve(directory + executionflag, datash->args, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &processstate, WUNTRACED);
		} while (!WIFEXITED(processstate) && !WIFSIGNALED(processstate));
	}

	datash->status = processstate / 256;
	return (1);
}
