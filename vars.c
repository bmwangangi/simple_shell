#include "shell.h"

/**
 * it_is_chain - test if current char is a chain delimeter
 * @infomation: the parameter struct
 * @buffer: the char buffer
 * @a: address of current position
 *
 * Return: 1
 */
int it_is_chain(info_t *infomation, char *buffer, size_t *a)
{
	size_t b = *a;

	if (buffer[b] == '|' && buffer[b + 1] == '|')
	{
		buffer[b] = 0;
		b++;
		infomation->cmd_buf_type = CMD_OR;
	}
	else if (buffer[b] == '&' && buffer[b + 1] == '&')
	{
		buffer[b] = 0;
		b++;
		infomation->cmd_buf_type = CMD_AND;
	}
	else if (buffer[b] == ';')
	{
		buffer[b] = 0;
		infomation->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*a = b;
	return (1);
}

/**
 * checking_the_chain - checks if we comtonue chaining
 * @infomation: the parameter struct
 * @buffer: the char buffer
 * @a: address of buffer
 * @b: starting position in buffer
 * @length: length of buffer
 *
 * Return: Void
 */
void check_the_chain(info_t *infomation, char *buffer, size_t *a, size_t b, size_t length)
{
	size_t c = *a;

	if (infomation->cmd_buf_type == CMD_AND)
	{
		if (infomation->status)
		{
			buffer[b] = 0;
			c = length;
		}
	}
	if (infomation->cmd_buf_type == CMD_OR)
	{
		if (!infomation->status)
		{
			buffer[b] = 0;
			c = length;
		}
	}

	*a = c;
}

/**
 * replacing_alias - replaces an alias
 * @infomation: the parameter struct
 *
 * Return: 1
 */
int replacing_alias(info_t *infomation)
{
	int a;
	list_t *node;
	char *b;

	for (a = 0; a < 10; a++)
	{
		node = node_start(infomation->alias, infomation->argv[0], '=');
		if (!node)
			return (0);
		free(infomation->argv[0]);
		b = _strchra(node->str, '=');
		if (!b)
			return (0);
		b = _strdup(b + 1);
		if (!b)
			return (0);
		infomation->argv[0] = b;
	}
	return (1);
}

/**
 * replacing_vars - replaces vars
 * @infomation: the parameter struct
 *
 * Return: 1
 */
int replacing_vars(info_t *infomation)
{
	int a = 0;
	list_t *node;

	for (a = 0; infomation->argv[a]; a++)
	{
		if (infomation->argv[a][0] != '$' || !infomation->argv[a][1])
			continue;

		if (!_strcmp(infomation->argv[a], "$?"))
		{
			replacing_string(&(infomation->argv[a]),
				_strdup(convert_number(infomation->status, 10, 0)));
			continue;
		}
		if (!_strcmp(infomation->argv[a], "$$"))
		{
			replacing_string(&(infomation->argv[a]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_start(infomation->env, &infomation->argv[a][1], '=');
		if (node)
		{
			replacing_string(&(infomation->argv[a]),
				_strdup(_strchra(node->str, '=') + 1));
			continue;
		}
		replacing_string(&infomation->argv[a], _strdup(""));

	}
	return (0);
}

/**
 * replacing_string - replaces string
 * @old: address of old
 * @new: new str
 *
 * Return: 1
 */
int replacing_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
