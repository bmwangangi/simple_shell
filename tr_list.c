#include "main.h"

/**
 * add_sep_node_end - used for separation
 * @head: the start of the list
 * @sep: holds the separator.
 * Return: address.
 */
sep_list *add_sep_node_end(sep_list **head, char sep)
{
	sep_list *old;
	sep_list *temperature;

	old = malloc(sizeof(sep_list));
	if (old == NULL)
		return (NULL);

	old->separator = sep;
	old->next = NULL;
	temperature = *head;

	if (temperature == NULL)
	{
		*head = old;
	}
	else
	{
		while (temperature->next != NULL)
			temperature = temperature->next;
		temperature->next = old;
	}

	return (*head);
}

/**
 * free_sep_list - used to free the list
 * @head: the start of the list
 * Return: 0
 */
void free_sep_list(sep_list **head)
{
	sep_list *temperature;
	sep_list *current;

	if (head != NULL)
	{
		current = *head;
		while ((temperature = current) != NULL)
		{
			current = current->next;
			free(temperature);
		}
		*head = NULL;
	}
}

/**
 * add_line_node_end - used for addition of command
 * @head: start of the list
 * @line: the cmd that has the line.
 * Return: address
 */
line_list *add_line_node_end(line_list **head, char *line)
{
	line_list *old, *temperature;

	old = malloc(sizeof(line_list));
	if (old == NULL)
		return (NULL);

	old->line = line;
	old->next = NULL;
	temperature = *head;

	if (temperature == NULL)
	{
		*head = old;
	}
	else
	{
		while (temperature->next != NULL)
			temperature = temperature->next;
		temperature->next = old;
	}

	return (*head);
}

/**
 * free_line_list - used to free the line
 * @head: start of the list
 * Return: 0
 */
void free_line_list(line_list **head)
{
	line_list *temperature;
	line_list *current;

	if (head != NULL)
	{
		current = *head;
		while ((temperature = current) != NULL)
		{
			current = current->next;
			free(temperature);
		}
		*head = NULL;
	}
}
