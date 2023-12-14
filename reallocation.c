#include "shell.h"

/**
 **_memoryset - fills memory with byte
 *@c: pointer to the memory
 *@d: byte to fill *c 
 *@e: amount of bytes 
 *Return: (c) a pointer
 */
char *_memoryset(char *c, char d, unsigned int e)
{
	unsigned int a;

	for (a = 0; a < e; a++)
		c[a] = d;
	return (c);
}

/**
 * for_free - frees a string holding other strings
 * @p: string holding other strings
 */
void for_free(char **p)
{
	char **b = p;

	if (!p)
		return;
	while (*p)
		free(*p++);
	free(b);
}

/**
 * _reallocation - reallocates  memory
 * @ptr: pointer 
 * @old_size: byte size 
 * @new_size: byte size
 *
 * Return: pointer
 */
void *_reallocation(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *a;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	a = malloc(new_size);
	if (!a)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		a[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (a);
}
