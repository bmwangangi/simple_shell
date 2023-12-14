#include "shell.h"

/**
 * get_histo_file - gets the file with history
 * @infomation: the struct parameter
 *
 * Return: allocated string
 */

char *get_histo_file(info_t *infomation)
{
	char *buffer, *directory;

	directory = _getenv(infomation, "HOME=");
	if (!directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, directory);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * writing_history - creates a file and conncts it with an existing one
 * @infomation: the struct
 *
 * Return: 1 
 */
int writing_history(info_t *infomation)
{
	ssize_t filed;
	char *filename = get_history_file(infomation);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	filed = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (filed == -1)
		return (-1);
	for (node = infomation->history; node; node = node->next)
	{
		_putsfd(node->str, filed);
		_putfd('\n', filed);
	}
	_putfd(BUF_FLUSH, filed);
	close(filed);
	return (1);
}

/**
 * reading_history - reads the history from a file
 * @infomation: the struct
 *
 * Return: histcount on success, 0 otherwise
 */
int reading_history(info_t *infomation)
{
	int a, late = 0, linecalculation = 0;
	ssize_t filed, rdlen, filesize = 0;
	struct stat st;
	char *buffer = NULL, *filename = get_history_file(infomation);

	if (!filename)
		return (0);

	filed = open(filename, O_RDONLY);
	free(filename);
	if (filed == -1)
		return (0);
	if (!fstat(filed, &st))
		filesize = st.st_size;
	if (filesize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (filesize + 1));
	if (!buffer)
		return (0);
	rdlen = read(filed, buffer, filesize);
	buffer[filesize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(filed);
	for (a = 0; a < filesize; a++)
		if (buffer[a] == '\n')
		{
			buffer[a] = 0;
			build_history_list(infomation, buffer + late, linecalculation++);
			late = a + 1;
		}
	if (late != a)
		build_history_list(infomation, buffer + late, linecalculation++);
	free(buffer);
	infomation->histcount = linecalculation;
	while (infomation->histcount-- >= HIST_MAX)
		delete_node_at_index(&(infomation->history), 0);
	renumber_history(infomation);
	return (infomation->histcount);
}

/**
 * building_history_list - adds entry to a history  list
 * @infomation: Structure containing  args.
 * @buffer: buffer
 * @linecount: the history adder
 *
 * Return: Always 0
 */
int building_history_list(info_t *infomation, char *buffer, int linecount)
{
	list_t *node = NULL;

	if (infomation->history)
		node = infomation->history;
	add_node_end(&node, buffer, linecount);

	if (!infomation->history)
		infomation->history = node;
	return (0);
}

/**
 * renumbered_history - renumbers the history 
 * @information: Structure containing args
 *
 * Return: the new histcount
 */
int renumbered_history(info_t *infomation)
{
	list_t *node = infomation->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (infomation->histcount = a);
}
