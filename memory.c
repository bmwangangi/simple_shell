#include "shell.h"

/**
 * befree - frees a pointer with it address
 * @pointer: address of the pointer
 *
 * Return: 1 if freed, otherwise 0.
 */
int befree(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
