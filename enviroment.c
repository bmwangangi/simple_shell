#include "shell.h"

/**
 * _myenviroment - prints the current environment
 * @trab: Structure containing potential arguments.
 * Return: Always 0
 */
int _myenviroment(info_t *trab)
{
	print_list_str(trab->env);
	return (0);
}

/**
 * _getenviroment - gets the value of the enviroment
 * @trab: Structure containing information
 * @sharon: the envirroment variable name
 *
 * Return value
 */
char *_getenvroment(info_t *trab, const char *sharon)
{
	list_t *node = trab->env;
	char *a;

	while (node)
	{
	a = starts_with(node->str, sharon);
		if (a && *a)
			return (a);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenviroment - Initialize an enviroment variable
 * @trab: Structure containing potential arguments.
 *
 *  Return: Always 0
 */
int _mysetenviroment(info_t *trab)
{
	if (trab->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(trab, trab->argv[1], trab->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenviroment - Remove the enviroment variable
 * @trab: Structure containing he arguments
 *  Return: Always 0
 */
int _myunsetenviroment(info_t *trab)
{
	int a;

	if (trab->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= trab->argc; a++)
		_unsetenv(trab, trab->argv[a]);

	return (0);
}

/**
 * populate_enviroment_list - used to populate the enviroment linked list
 * @trab: Structure containing the arguments
 *
 * Return: Always 0
 */
int populate_enviroment_list(info_t *trab)
{
	list_t *node = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_end(&node, environ[a], 0);
	trab->env = node;
	return (0);
}
