#include "shell.h"

/**
 * get_environment - returns the string array
 * @trab: Structure containing arguments
 * Return: Always 0
 */
char **get_environment(info_t *trab)
{
	if (!trab->environ || trab->env_changed)
	{
		trab->environ = list_to_strings(trab->env);
		trab->env_changed = 0;
	}

	return (trab->environ);
}

/**
 * _unsetenviroment - Remove an environment
 * @trab: Structure containing arguments
 *  Return: 1 on delete, 0 otherwise
 * @variable: the string enviroment variable property
 */
int _unsetenviroment(info_t *trab, char *variable)
{
	list_t *node = trab->env;
	size_t a = 0;
	char *b;

	if (!node || !variable)
		return (0);

	while (node)
	{
		b = starts_with(node->str, variable);
		if (b && *b == '=')
		{
			trab->env_changed = delete_node_at_index(&(trab->env), a);
			a = 0;
			node = trab->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (trab->env_changed);
}

/**
 * _setenviroment - a new environment
 * @trab: Structure containing args
 * @variable: the string env var property
 * @valu: the string enirome variable
 *  Return: Always 0
 */
int _setenviroment(info_t *trab, char *variable, char *valu)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!variable || !valu)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(valu) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, valu);
	node = trab->env;
	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			trab->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(trab->env), buffer, 0);
	free(buffer);
	trab->env_changed = 1;
	return (0);
}
