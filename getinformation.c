#include "shell.h"

/**
 * clearing_info - initializes a struct for info
 * @information: struct address
 */
void clearing_info(info_t *infomation)
{
	infomation->arg = NULL;
	infomation->argv = NULL;
	infomation->path = NULL;
	infomation->argc = 0;
}

/**
 * setting_info - initilises a struct for info
 * @infomation: the struct address
 * @ar: argument vector
 */
void setting_info(info_t *infomation, char **ar)
{
	int a = 0;

	infomation->fname = ar[0];
	if (infomation->arg)
	{
		infomation->argv = strtow(infomation->arg, " \t");
		if (!infomation->argv)
		{

			infomation->argv = malloc(sizeof(char *) * 2);
			if (infomation->argv)
			{
				infomation->argv[0] = _strdup(infomation->arg);
				infomation->argv[1] = NULL;
			}
		}
		for (a = 0; infomation->argv && infomation->argv[a]; a++)
			;
		infomation->argc = a;

		replace_alias(infomation);
		replace_vars(infomation);
	}
}

/**
 * free_infomation - frees info
 * @infomation: struct address
 * @fully: free all fields
 */
void free_infomation(info_t *infomation, int fully)
{
	ffree(infomation->argv);
	infomation->argv = NULL;
	infomation->path = NULL;
	if (fully)
	{
		if (!infomation->cmd_buf)
			free(infomation->arg);
		if (infomation->env)
			free_list(&(infomation->env));
		if (infomation->history)
			free_list(&(infomation->history));
		if (infomation->alias)
			free_list(&(infomation->alias));
		ffree(infomation->environ);
			infomation->environ = NULL;
		bfree((void **)infomation->cmd_buf);
		if (infomation->readfd > 2)
			close(infomation->readfd);
		_putchar(BUF_FLUSH);
	}
}
