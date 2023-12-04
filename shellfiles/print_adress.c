#include <stdio.h>
#include <stdlib.h>

/**
 * print_address - Prints the address
 *
 * @argc: the argument count
 * @argv: the argument vector
 * @command_enviroment: An array
 *
 * Return: 0
 */
int print_address(int argc, char *argv[], char *command_enviroment[])
{
	extern char **environ;

	printf("Address of command_enviroment: %p\n", (void *)command_enviroment);
	printf("Address of environ: %p\n", (void *)environ);
	return 0;
}

/**
 * main - always the entry point of the program.
 *
 * @argc: argumen count
 * @argv: argument vector
 * @enviroment: am array
 *
 * Return: 0
 */
int main(int argc, char *argv[], char *enviroment[])
{
	print_address(argc, argv, enviroment);
	
	return 0;
}

