#include "main.h"

/**
 * add_rvar_node - adds a variable at the end
 * @start: start of the list
 * @avar: len of the var
 * @variable: the var value.
 * @lowerval: len of the variable
 * Return: address.
 */
r_var *add_rvar_node(r_var **start, int avar, char *variable, int lowerval)
{
	r_var *old, *temperature;

	old = malloc(sizeof(r_var));
	if (old == NULL)
		return (NULL);

	old->len_var = avar;
	old->val = variable;
	old->len_val = lowerval;

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
 * free_rvar_list - used to free the variable list
 * @start: start of the list
 * Return: 0
 */
void free_rvar_list(r_var **start)
{
	r_var *temperature;
	r_var *current;

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
