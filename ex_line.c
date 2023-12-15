#include "main.h"

/**
 * exec_line - finds built commands
 * @datashel: data holding the onfomation
 * Return: 1
 */
int exec_line(d_shell *datashel)
{
	int (*builtin)(d_shell *datashel);

	if (datashel->args[0] == NULL)
		return (1);

	builtin = get_builtin(datashel->args[0]);

	if (builtin != NULL)
		return (builtin(datashel));

	return (cmd_exec(datashel));
}
