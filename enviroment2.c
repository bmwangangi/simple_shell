#include "main.h"

/**
 * copy_info - used to copy the information created
 * @joe: the variable
 * @val: used for storing values
 * Return: env
 */
char *copy_info(char *joe, char *val)
{
	char *newvalue;
	int length_name, length_value, length;

	length_name = _strlen(joe);
	length_value = _strlen(val);
	length = length_name + length_value + 2;
	newvalue = malloc(sizeof(char) * (length));
	_strcpy(newvalue, joe);
	_strcat(newvalue, "=");
	_strcat(newvalue, val);
	_strcat(newvalue, "\0");

	return (newvalue);
}

/**
 * set_env - used to set a new env variable
 * @joe: the env variable
 * @val: the value of the variable
 * @datashel: the data holding the info
 * Return: 0
 */
void set_env(char *joe, char *val, d_shell *datashel)
{
	int a;
	char *variable_env, *name_enviroment;

	for (a = 0; datashel->_environ[a]; a++)
	{
		variable_env = _strdup(datashel->_environ[a]);
		name_enviroment = _strtok(variable_env, "=");
		if (_strcmp(name_enviroment, joe) == 0)
		{
			free(datashel->_environ[a]);
			datashel->_environ[a] = copy_info(name_enviroment, val);
			free(variable_env);
			return;
		}
		free(variable_env);
	}

	datashel->_environ = _reallocdp(datashel->_environ, a,
			sizeof(char *) * (a + 2));
	datashel->_environ[a] = copy_info(joe, val);
	datashel->_environ[a + 1] = NULL;
}

/**
 * _setenv - used to copmare env variables
 * @datashel: the data holding info
 * Return: 1
 */
int _setenv(d_shell *datashel)
{

	if (datashel->args[1] == NULL || datashel->args[2] == NULL)
	{
		get_error(datashel, -1);
		return (1);
	}

	set_env(datashel->args[1], datashel->args[2], datashel);

	return (1);
}

/**
 * _unsetenv - used to delete env var
 * @datashel: The data holding the infoMATION OF THE FILE
 * Return: 1
 */
int _unsetenv(d_shell *datashel)
{
	char **realloc_environment;
	char *variable_env, *name_enviroment;
	int a, b, c;

	if (datashel->args[1] == NULL)
	{
		get_error(datashel, -1);
		return (1);
	}
	c = -1;
	for (a = 0; datashel->_environ[a]; a++)
	{
		variable_env = _strdup(datashel->_environ[a]);
		name_enviroment = _strtok(variable_env, "=");
		if (_strcmp(name_enviroment, datashel->args[1]) == 0)
		{
			c = a;
		}
		free(variable_env);
	}
	if (c == -1)
	{
		get_error(datashel, -1);
		return (1);
	}
	realloc_environment = malloc(sizeof(char *) * (a));
	for (a = b = 0; datashel->_environ[a]; a++)
	{
		if (a != c)
		{
			realloc_environment[b] = datashel->_environ[a];
			b++;
		}
	}
	realloc_environment[b] = NULL;
	free(datashel->_environ[c]);
	free(datashel->_environ);
	datashel->_environ = realloc_environment;
	return (1);
}
