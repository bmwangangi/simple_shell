#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * print_env - used to print the enviroment
 *
 * This function iterates through the environment variables and prints each one.
 */
void print_env(void)
{
	extern char **environ;

	char **enviroment;
	
	for (enviroment = environ; *enviroment != NULL; enviroment++)
	{
		printf("%s\n", *enviroment);
	}
}

/**
 * main - always the entry point of the program.
 *
 * Return: Always 0 (success).
 */
int main(void)
{
    /* Call the function to print the environment */
    print_env();

    return (0);
}

