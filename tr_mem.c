#include "main.h"

/**
 * _memcpy - used to copy memory information
 * @newpointer: where our pointer will go
 * @pointer: our original  pointer
 * @val: the pointer size
 *
 * Return: 0
 */
void _memcpy(void *newpointer, const void *pointer, unsigned int val)
{
	char *char_pointer = (char *)pointer;
	char *char_newpointer = (char *)newpointer;
	unsigned int a;

	for (a = 0; a < val; a++)
		char_newpointer[a] = char_pointer[a];
}

/**
 * _realloc - used to reallocate the memory of a block
 * @pointer: points to the mem
 * @o_size: represents the bites allocated
 * @n_size: reporesentsa the memory alocated
 *
 * Return: pointer
 */
void *_realloc(void *pointer, unsigned int o_size, unsigned int n_size)
{
	void *newpointer;

	if (pointer == NULL)
		return (malloc(n_size));

	if (n_size == 0)
	{
		free(pointer);
		return (NULL);
	}

	if (n_size == o_size)
		return (pointer);

	newpointer = malloc(n_size);
	if (newpointer == NULL)
		return (NULL);

	if (n_size < o_size)
		_memcpy(newpointer, pointer, n_size);
	else
		_memcpy(newpointer, pointer, o_size);

	free(pointer);
	return (newpointer);
}

/**
 * _reallocdp - used to allocate memory for double ptr
 * @pointer: the double pointer
 * @o_size: the opointer
 * @n_size: nthe new pointer
 *
 * Return: pointer
 */
char **_reallocdp(char **pointer, unsigned int o_size, unsigned int n_size)
{
	char **newpointer;
	unsigned int a;

	if (pointer == NULL)
		return (malloc(sizeof(char *) * n_size));

	if (n_size == o_size)
		return (pointer);

	newpointer = malloc(sizeof(char *) * n_size);
	if (newpointer == NULL)
		return (NULL);

	for (a = 0; a < o_size; a++)
		newpointer[a] = pointer[a];

	free(pointer);

	return (newpointer);
}
