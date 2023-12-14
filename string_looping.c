#include "shell.h"

/**
 * hsh - the shell loop
 * @infomation: return info struct
 * @ar: the argument vector
 *
 * Return: 0
 */
int hsh(info_t *infomation, char **ar)
{
	ssize_t a = 0;
	int builtin_ret = 0;

	while (a != -1 && builtin_ret != -2)
	{
		clear_info(infomation);
		if (interactive(infomation))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		a = get_input(infomation);
		if (a != -1)
		{
			set_info(infomation, ar);
			builtin_ret = find_builtin(infomation);
			if (builtin_ret == -1)
				find_cmd(infomation);
		}
		else if (interactive(infomation))
			_putchar('\n');
		free_info(infomation, 0);
	}
	write_history(infomation);
	free_info(infomation, 1);
	if (!interactive(infomation) && infomation->status)
		exit(infomation->status);
	if (builtin_ret == -2)
	{
		if (infomation->err_num == -1)
			exit(infomation->status);
		exit(infomation->err_num);
	}
	return (builtin_ret);
}

/**
 * find_the_builtin - finds a command thet is alresdy built in
 * @infomation:return info struct
 *
 * Return: always the output
 */
int find_the_builtin(info_t *infomation)
{
	int a, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (a = 0; builtintbl[a].type; a++)
		if (_strcmp(infomation->argv[0], builtintbl[a].type) == 0)
		{
			infomation->line_count++;
			built_in_ret = builtintbl[a].func(infomation);
			break;
		}
	return (built_in_ret);
}

/**
 * finding_cmd - fining command paths
 * @infomation: return info struct
 *
 * Return: void
 */
void finding_cmd(info_t *infomation)
{
	char *path = NULL;
	int a, b;

	infomation->path = infomation->argv[0];
	if (infomation->linecount_flag == 1)
	{
		infomation->line_count++;
		infomation->linecount_flag = 0;
	}
	for (a = 0, b = 0; infomation->arg[a]; a++)
		if (!is_delim(infomation->arg[a], " \t\n"))
			b++;
	if (!b)
		return;

	path = find_path(infomation, _getenv(infomation, "PATH="), infomation->argv[0]);
	if (path)
	{
		infomation->path = path;
		fork_cmd(infomation);
	}
	else
	{
		if ((interactive(infomation) || _getenv(infomation, "PATH=")
			|| infomation->argv[0][0] == '/') && is_cmd(infomation, infomation->argv[0]))
			fork_cmd(infomation);
		else if (*(infomation->arg) != '\n')
		{
			infomation->status = 127;
			print_error(infomation, "not found\n");
		}
	}
}

/**
 * forking_cmd - forks a an exit thread
 * @infomation: return info struct
 *
 * Return: void
 */
void forking_cmd(info_t *infomation)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(infomation->path, infomation->argv, get_environ(infomation)) == -1)
		{
			free_info(infomation, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(infomation->status));
		if (WIFEXITED(infomation->status))
		{
			infomation->status = WEXITSTATUS(infomation->status);
			if (infomation->status == 126)
				print_error(infomation, "Permission denied\n");
		}
	}
}
