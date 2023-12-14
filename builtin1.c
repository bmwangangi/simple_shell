#include "shell.h"

/**
 * _myhisto - displays the history list
 * @trab: Structure containing arguments
 *  Return: Always 0
 */
int _myhisto(info_t *trab)
{
	printing_list(trab->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @trab: parameter struct
 * @str: the string
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *trab, char *str)
{
	char *a, b;
	int ret;

	a = _strchra(str, '=');
	if (!a)
		return (1);
	b = *a;
	*a = 0;
	ret = deleting_node(&(trab->alias),
		get_index(trab->alias, node_start(trab->alias, str, -1)));
	*a = b;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @trab: parameter struct
 * @str: the string 
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *trab, char *str)
{
	char *a;

	a = _strchra(str, '=');
	if (!a)
		return (1);
	if (!*++a)
		return (unset_alias(trab, str));

	unset_alias(trab, str);
	return (adding_node_end(&(trab->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *b = NULL, *a = NULL;

	if (node)
	{
		b = _strchra(node->str, '=');
		for (a = node->str; a <= b; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the allias
 * @trab: Structure containing arguments
 *  Return: Always 0
 */
int _myalias(info_t *trab)
{
	int i = 0;
	char *b = NULL;
	list_t *node = NULL;

	if (trab->argc == 1)
	{
		node = trab->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; trab->argv[i]; i++)
	{
		b = _strchra(trab->argv[i], '=');
		if (b)
			set_alias(trab, trab->argv[i]);
		else
			print_alias(node_start(trab->alias, trab->argv[i], '='));
	}

	return (0);
}
