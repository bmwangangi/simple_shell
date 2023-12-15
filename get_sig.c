#include "main.h"

/**
 * get_sigint - handling the control c
 * @signal: Sgn handlimg
 */
void get_sigint(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
