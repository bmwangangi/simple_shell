#include "shell.h"

/**
 * it_is_cmd - determines if it an executable command
 * @infomation: the info struct
 * @way: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int it_is_cmd(info_t *infomation, char *way)
{
	struct stat st;

	(void)infomation;
	if (!way || stat(way, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_chars - duplicates the  char
 * @pathstring: the string of the path
 * @start: start
 * @stop: stop
 *
 * Return: pointer
 */
char *duplicate_chars(char *pathstring, int start, int stop)
{
	static char buf[1024];
	int a = 0, b = 0;

	for (b = 0, a = start; a < stop; a++)
		if (pathstring[a] != ':')
			buf[b++] = pathstring[a];
	buf[b] = 0;
	return (buf);
}

/**
 * finding_the__path - finds this cmd
 * @infomation: the infomation  struct
 * @pathstring: the  string of the path
 * @cmd: the cmd to find
 *
 * Return: fully the path
 */
char *finding_the_path(info_t *infomation, char *pathstring, char *cmd)
{
	int a = 0, current_pos = 0;
	char *path;

	if (!pathstring)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(infomation, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstring[a] || pathstring[a] == ':')
		{
			path = dup_chars(pathstring, current_pos, a);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(infomation, path))
				return (path);
			if (!pathstring[a])
				break;
			current_pos = a;
		}
		a++;
	}
	return (NULL);
}
