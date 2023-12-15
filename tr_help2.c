#include "main.h"

/**
 * aux_help - Holds the help information
 * Return: 0
 */
void aux_help(void)
{
	char *helping = "help: helping you [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, helping, _strlen(helping));
	helping = "\tDisplay info.\n ";
	write(STDOUT_FILENO, helping, _strlen(helping));
	helping = "Displays summaries.\n";
	write(STDOUT_FILENO, helping, _strlen(helping));
}
/**
 * aux_help_alias - Holds the help information
 * Return: 0
 */
void aux_help_alias(void)
{
	char *helping = "aliaings: aliasing [-p] [name[=the value]...]\n";

	write(STDOUT_FILENO, helping, _strlen(helping));
	helping = "\tdisplay aliases.\n ";
	write(STDOUT_FILENO, helping, _strlen(helping));
}
/**
 * aux_help_cd - Holds the help information
 * Return: 0
 */
void aux_help_cd(void)
{
	char *helping = "cd: cd [-L|[-P [-e]] [-@]] [directory]\n";

	write(STDOUT_FILENO, helping, _strlen(helping));
	helping = "\tChange the working dir.\n ";
	write(STDOUT_FILENO, helping, _strlen(helping));
}
