#include "main.h"

/**
 * add_sep_node_end - used for separation
 * @start: the start of the list
 * @separate: holds the separator.
 * Return: address.
 */
sep_list *add_sep_node_end(sep_list **start, char separate)
{
	sep_list *old;
	sep_list *temperature;

	old = malloc(sizeof(sep_list));
	if (old == NULL)
		return (NULL);

	old->separator = separate;
	old->next = NULL;
	temperature = *start;

	if (temperature == NULL)
	{
		*start = old;
	}
	else
	{
		while (temperature->next != NULL)
			temperature = temperature->next;
		temperature->next = old;
	}

	return (*start);
}

/**
 * free_sep_list - used to free the list
 * @start: the start of the list
 * Return: 0
 */
void free_sep_list(sep_list **start)
{
	sep_list *temperature;
	sep_list *current;

	if (start != NULL)
	{
		current = *start;
		while ((temperature = current) != NULL)
		{
			current = current->next;
			free(temperature);
		}
		*start = NULL;
	}
}

/**
 * add_line_node_end - used for addition of command
 * @start: start of the list
 * @str: the cmd that has the line.
 * Return: address
 */
line_list *add_line_node_end(line_list **start, char *str)
{
	line_list *old, *temperature;

	old = malloc(sizeof(line_list));
	if (old == NULL)
		return (NULL);

	old->line = str;
	old->next = NULL;
	temperature = *start;

	if (temperature == NULL)
	{
		*start = old;
	}
	else
	{
		while (temperature->next != NULL)
			temperature = temperature->next;
		temperature->next = old;
	}

	return (*start);
}

/**
 * free_line_list - used to free the line
 * @start: start of the list
 * Return: 0
 */
void free_line_list(line_list **start)
{
	line_list *temperature;
	line_list *current;

	if (start != NULL)
	{
		current = *start;
		while ((temperature = current) != NULL)
		{
			current = current->next;
			free(temperature);
		}
		*start = NULL;
	}
}
