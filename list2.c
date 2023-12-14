#include "shell.h"

/**
 * listing_len - length of linked list
 * @a: pointer to  node
 *
 * Return: size of list
 */
size_t listing_len(const list_t *a)
{
	size_t b = 0;

	while (a)
	{
		a = a->next;
		b++;
	}
	return (b);
}

/**
 * list_to_the_strings - returns an array
 * @start: pointer to  node
 *
 * Return: array
 */
char **list_to_the_strings(list_t *start)
{
	list_t *node = start;
	size_t b = list_len(start), c;
	char **str;
	char *strs;

	if (!start || !b)
		return (NULL);
	str = malloc(sizeof(char *) * (b + 1));
	if (!str)
		return (NULL);
	for (b = 0; node; node = node->next, b++)
	{
		strs = malloc(_strlen(node->str) + 1);
		if (!strs)
		{
			for (c = 0; c < b; c++)
				free(str[c]);
			free(str);
			return (NULL);
		}

		strs = _strcpy(strs, node->str);
		str[b] = strs;
	}
	str[b] = NULL;
	return (str);
}


/**
 * printing_list - print elements
 * @a: pointer to node
 *
 * Return: list
 */
size_t printing_list(const list_t *a)
{
	size_t b = 0;

	while (a)
	{
		_puts(convert_number(a->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(a->str ? a->str : "(nil)");
		_puts("\n");
		a = a->next;
		a++;
	}
	return (b);
}

/**
 * node_start - returns node with prefix
 * @node: pointer to head
 * @prx: string to match
 * @a: the next character to
 *
 * Return: match node or null
 */
list_t *node_start(list_t *node, char *prx, char a)
{
	char *b = NULL;

	while (node)
	{
		b = starts_with(node->str, prx);
		if (b && ((a == -1) || (*b == a)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_index - gets the index
 * @start: pointer to start
 * @node: pointer to node
 *
 * Return: index of node or -1
 */
ssize_t get_index(list_t *start, list_t *node)
{
	size_t a = 0;

	while (start)
	{
		if (start == node)
			return (a);
		start = start->next;
		a++;
	}
	return (-1);
}
