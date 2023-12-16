#include "main.h"

/**
 * get_sigint - handling the control c
 * @sig: Sgn handlimg
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
