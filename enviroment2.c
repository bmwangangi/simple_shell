#include "main.h"

/**
 * copy_info - used to copy the information created
 * @name: the variable
 * @value: used for storing values
 *
 * Return: env
 */
char *copy_info(char *name, char *value)
{
	char *newvalue;
	int length_name, length_value, length;

	length_name = _strlen(name);
	length_value = _strlen(value);
	length = length_name + length_value + 2;
	newvalue = malloc(sizeof(char) * (length));
	_strcpy(newvalue, name);
	_strcat(newvalue, "=");
	_strcat(newvalue, value);
	_strcat(newvalue, "\0");

	return (newvalue);
}

/**
 * set_env - used to set a new env variable
 *
 * @name: the env variable
 * @value: the value of the variable
 * @datash: the data holding the info
 * Return: 0
 */
void set_env(char *name, char *value, data_shell *datash)
{
	int a;
	char *variable_env, *name_enviroment;

	for (a = 0; datash->_environ[a]; a++)
	{
		variable_env = _strdup(datash->_environ[a]);
		name_enviroment = _strtok(variable_env, "=");
		if (_strcmp(name_enviroment, name) == 0)
		{
			free(datash->_environ[a]);
			datash->_environ[a] = copy_info(name_enviroment, value);
			free(variable_env);
			return;
		}
		free(variable_env);
	}

	datash->_environ = _reallocdp(datash->_environ, a, sizeof(char *) * (a + 2));
	datash->_environ[a] = copy_info(name, value);
	datash->_environ[a + 1] = NULL;
}

/**
 * _setenv - used to copmare env variables
 * @datash: the data holding info
 *
 * Return: 1
 */
int _setenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetenv - used to delete env var
 *
 * datash: the data holding the info
 *
 * Return: 1
 */
int _unsetenv(data_shell *datash)
{
	char **realloc_environment;
	char *variable_env, *name_enviroment;
	int a, b, c;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	c = -1;
	for (a = 0; datash->_environ[a]; a++)
	{
		variable_env = _strdup(datash->_environ[a]);
		name_enviroment = _strtok(variable_env, "=");
		if (_strcmp(name_enviroment, datash->args[1]) == 0)
		{
			c = a;
		}
		free(variable_env);
	}
	if (c == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	realloc_environment = malloc(sizeof(char *) * (a));
	for (a = b = 0; datash->_environ[a]; a++)
	{
		if (a != c)
		{
			realloc_environment[b] = datash->_environ[a];
			b++;
		}
	}
	realloc_environment[b] = NULL;
	free(datash->_environ[c]);
	free(datash->_environ);
	datash->_environ = realloc_environment;
	return (1);
}
