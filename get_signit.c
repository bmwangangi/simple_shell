#include "main.h"

/**
 * get_sigint - used for handling the signals
 * @sig: Sig no
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
