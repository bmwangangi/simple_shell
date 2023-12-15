#include "main.h"

/**
 * aux_help_env - Holds the hel information
 * Return: 0
 */
void aux_help_env(void)
{
	char *helping =
		"enviroment: enviroment [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, helping, _strlen(helping));
	helping = "Print the env of the shell.\n";
	write(STDOUT_FILENO, helping, _strlen(helping));

}
/**
 * aux_help_setenv - Holds the help informaations
 * Return: 0
 */
void aux_help_setenv(void)
{

	char *helping =
		"setenv:iroment setenviroment (const char *name, const char *value,";

	write(STDOUT_FILENO, helping, _strlen(helping));
	helping = "integer replace)\n\t";
	write(STDOUT_FILENO, helping, _strlen(helping));
	helping = "Add a new environment\n";
	write(STDOUT_FILENO, helping, _strlen(helping));
}
/**
 * aux_help_unsetenv - Holds the help information
 * Return: 0
 */
void aux_help_unsetenv(void)
{
	char *helping = "unsetenviroment: unsetenviroment (const char *name)\n\t";

	write(STDOUT_FILENO, helping, _strlen(helping));
	helping = "Remove an entry  environment\n";
	write(STDOUT_FILENO, helping, _strlen(helping));
}


/**
 * aux_help_general - Entry holding the help information
 * Return: 0
 */
void aux_help_general(void)
{
	char *helping = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, helping, _strlen(helping));
	helping = "These commands are predefined.Type 'help' to see the list";
	write(STDOUT_FILENO, helping, _strlen(helping));
	helping = "Type 'help name' to help'.\n\n ";
	write(STDOUT_FILENO, helping, _strlen(helping));
	helping = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, helping, _strlen(helping));
	helping = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, helping, _strlen(helping));
	helping = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, helping, _strlen(helping));
	helping = "unsetenv [variable]\n";
	write(STDOUT_FILENO, helping, _strlen(helping));
}
/**
 * aux_help_exit - Holds the help information
 * Return: 0
 */
void aux_help_exit(void)
{
	char *helping = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, helping, _strlen(helping));
	helping = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, helping, _strlen(helping));
	helping = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, helping, _strlen(helping));
}
