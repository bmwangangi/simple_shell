#include "main.h"

/**
 * _memcpy - used to copy memory information
 * @newptr: where our pointer will go
 * @ptr: our original  pointer
 * @size: the pointer size
 *
 * Return: 0
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_pointer = (char *)ptr;
	char *char_newpointer = (char *)newptr;
	unsigned int a;

	for (a = 0; a < size; a++)
		char_newpointer[a] = char_pointer[a];
}

/**
 * _realloc - used to reallocate the memory of a block
 * @ptr: points to the mem
 * @old_size: represents the bites allocated
 * @new_size: reporesentsa the memory alocated
 *
 * Return: pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newpointer;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newpointer = malloc(new_size);
	if (newpointer == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newpointer, ptr, new_size);
	else
		_memcpy(newpointer, ptr, old_size);

	free(ptr);
	return (newpointer);
}

/**
 * _reallocdp - used to allocate memory for double ptr
 * @ptr: the double pointer
 * @old_size: the opointer
 * @new_size: nthe new pointer
 *
 * Return: pointer
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newpointer;
	unsigned int a;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newpointer = malloc(sizeof(char *) * new_size);
	if (newpointer == NULL)
		return (NULL);

	for (a = 0; a < old_size; a++)
		newpointer[a] = ptr[a];

	free(ptr);

	return (newpointer);
}
