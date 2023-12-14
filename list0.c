#include "shell.h"

/**
 * adding_node - adds a node to thhe list
 * @start: address of pointer
 * @str: the  field of node
 * @number: the node index
 *
 * Return: size of list
 */
list_t *adding_node(list_t **start, const char *str, int number)
{
	list_t *new_head;

	if (!start)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = number;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *start;
	*start = new_head;
	return (new_head);
}

/**
 * adding_node_end - adds a node to the end
 * @start: pointer to head node
 * @str: field of node
 * @number: index used by history
 *
 * Return: size of list
 */
list_t *adding_node_end(list_t **start, const char *str, int number)
{
	list_t *new_node, *node;

	if (!start)
		return (NULL);

	node = *start;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = number;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*start = new_node;
	return (new_node);
}

/**
 * printing_list_str - prints the str element
 * @a: pointer
 *
 * Return: size of list
 */
size_t printing_list_str(const list_t *a)
{
	size_t b = 0;

	while (a)
	{
		_puts(a->str ? a->str : "(nil)");
		_puts("\n");
		a = a->next;
		b++;
	}
	return (b);
}

/**
 * deleting_node - deletes node
 * @start: pointer to node
 * @index: index of node
 *
 * Return: 1 on success, 0 on failure
 */
int deleting_node(list_t **start, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int a = 0;

	if (!start || !*start)
		return (0);

	if (!index)
	{
		node = *start;
		*start = (*start)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *start;
	while (node)
	{
		if (a == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		a++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_the_list - frees all nodes
 * @head_p:  pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_p)
{
	list_t *node, *next_node, *head;

	if (!head_p || !*head_p)
		return;
	head = *head_p;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_p = NULL;
}
