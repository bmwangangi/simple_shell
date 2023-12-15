#include "main.h"

/**
 * free_data - free struc:
 * @datashel: struc:
 * Return: no return
 */
void free_data(d_shell *datashel)
{
	unsigned int x;

	for (x = 0; datashel->_environ[x]; x++)
	{
		free(datashel->_environ[x]);
	}

	free(datashel->_environ);
	free(datashel->pid);
}

/**
 * set_data - init data struc:
 * @datashel: data struc:
 * @av: arg vect:
 * Return: return 0
 */
void set_data(d_shell *datashel, char **av)
{
	unsigned int a;

	datashel->av = av;
	datashel->input = NULL;
	datashel->args = NULL;
	datashel->status = 0;
	datashel->counter = 1;

	for (a = 0; environ[a]; a++);

	datashel->_environ = malloc(sizeof(char *) * (a + 1));

	for (a = 0; environ[a]; a++)
	{
		datashel->_environ[a] = _strdup(environ[a]);
	}

	datashel->_environ[a] = NULL;
	datashel->pid = aux_itoa(getpid());
}

/**
 * main - Entry point
 * @ac: arg count:
 * @av: arg vect:
 * Return: Always 0
 */
int main(int ac, char **av)
{
	d_shell datashel;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&datashel, av);
	shell_loop(&datashel);
	free_data(&datashel);
	if (datashel.status < 0)
		return (255);
	return (datashel.status);
}
