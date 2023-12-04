#include <stdio.h>
#include <stdlib.h>

/**
 * print_enviroment - Prints the enviroment using environ 
 * @env: array of environment variables
 *
 * Return: void
 */

void print_enviroment(char **enviroment)
{
	int a = 0;

	while (enviroment[a] != NULL)
	{
		printf("%s\n", enviroment[a]);
		a++;
	}
}
