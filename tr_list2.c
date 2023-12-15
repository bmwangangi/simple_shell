#include "main.h"

/**
 * add_rvar_node - adds a variable at the end
 * @head: start of the list
 * @lvar: len of the var
 * @val: the var value.
 * @lval: len of the variable
 * Return: address.
 */
r_var *add_rvar_node(r_var **head, int lvar, char *val, int lval)
{
	r_var *old, *temperature;

	old = malloc(sizeof(r_var));
	if (old == NULL)
		return (NULL);

	old->len_var = lvar;
	old->val = val;
	old->len_val = lval;

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
 * free_rvar_list - used to free the variable list
 * @head: start of the list
 * Return: 0
 */
void free_rvar_list(r_var **head)
{
	r_var *temperature;
	r_var *current;

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
